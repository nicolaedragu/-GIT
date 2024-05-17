#include "utils.hpp"

using namespace std;

void close_connections(vector<client> &clients, int udp_sock, int tcp_sock, fd_set read_fds);

// function to send messages to subscribers
void send_messages(vector<client> &clients, tcp_message *tcp_message)
{
    for (auto &client : clients)
    {
        if (client.connected)
        {
            for (auto &topic : client.topics)
            {
                if (strcmp(topic.c_str(), tcp_message->topic) == 0)
                {
                    int ret = send(client.socket, tcp_message, sizeof(tcp_message), 0);
                    DIE(ret < 0, "Error sending message to subscriber");
                }
            }
        }
    }
}

// function to parse UDP messages into readable format
void make_readable(tcp_message *tcp_message, udp_message *udp_message, sockaddr_in client_addr)
{
    strcpy(tcp_message->topic, udp_message->topic);

    if (udp_message->data_type == 0)
    { // INT
        strcpy(tcp_message->data_type, "INT");
        int value;
        value = ntohl(*(uint32_t *)(udp_message->contents + 1));
        char sign = udp_message->contents[0];
        if (sign == 1)
        {
            value = -value;
        }
        sprintf(tcp_message->contents, "%d", value);
    }
    else if (udp_message->data_type == 1)
    { // SHORT_REAL
        strcpy(tcp_message->data_type, "SHORT_REAL");
        double value;
        value = ntohs(*(uint16_t *)(udp_message->contents + 1));
        value = value / 100;
        sprintf(tcp_message->contents, "%.2f", value);
    }
    else if (udp_message->data_type == 2)
    { // FLOAT
        strcpy(tcp_message->data_type, "FLOAT");
        float value;
        value = ntohs(*(uint32_t *)(udp_message->contents + 1));
        char sign = udp_message->contents[0];
        if (sign == 1)
        {
            value = -value;
        }

        // first 4 bytes are the value
        // udp_message->contents[5] is the power of 10 (uint8_t) meaning one byte
        value = value / pow(10, udp_message->contents[5]);
        sprintf(tcp_message->contents, "%f", value);
    }
    else if (udp_message->data_type == 3)
    { // STRING
        strcpy(tcp_message->data_type, "STRING");
        string value(udp_message->contents);
        strcpy(tcp_message->contents, value.c_str());
    }

    // set the IP and port of the client
    strcpy(tcp_message->ip_client, inet_ntoa(client_addr.sin_addr));
    tcp_message->port_client = client_addr.sin_port;
}

// function to find client by id
client *find_client_by_id(vector<client> &clients, string id)
{
    for (auto &client : clients)
    {
        if (client.id == id)
        {
            return &client;
        }
    }
    return NULL;
}

// function to find client by socket
client *find_client_by_socket(vector<client> &clients, int socket)
{
    for (auto &client : clients)
    {
        if (client.socket == socket)
        {
            return &client;
        }
    }
    return NULL;
}

void handle_stdin(char *buffer, vector<client> &clients, int udp_sock, int tcp_sock, fd_set &read_fds)
{
    fgets(buffer, BUFFLEN, stdin);
    if (strncmp(buffer, "exit", 4) == 0)
    {
        close_connections(clients, udp_sock, tcp_sock, read_fds);
        exit(EXIT_SUCCESS);
    }
    else
    {
        fprintf(stderr, "Invalid command.\n");
    }
}

void handle_udp_socket(int i, vector<client> &clients, udp_message &udp_message, tcp_message &tcp_message, sockaddr_in &client_addr)
{
    memset(&udp_message, 0, sizeof(udp_message));
    memset(&tcp_message, 0, sizeof(tcp_message));

    // Receive message from UDP client
    socklen_t len = sizeof(client_addr);
    int ret = recvfrom(i, &udp_message, sizeof(udp_message), 0, (sockaddr *)&client_addr, &len);
    DIE (ret < 0, "Error receiving message from UDP client");

    // Parse UDP message
    make_readable(&tcp_message, &udp_message, client_addr);

    // Send message to all clients
    send_messages(clients, &tcp_message);
}

void handle_tcp_socket(int i, vector<client> &clients, fd_set &read_fds, char *buffer, sockaddr_in &client_addr, int &fdmax)
{
    // Accept new TCP connection
    socklen_t len = sizeof(client_addr);
    int new_sock = accept(i, (sockaddr *)&client_addr, &len);
    DIE (new_sock < 0, "Error accepting TCP connection");
    // Disable Nagle's algorithm
    
    int nagle = 1;
    int ret = setsockopt(new_sock, IPPROTO_TCP, TCP_NODELAY, &nagle, sizeof(int));
    DIE(ret < 0, "Error disabling Nagle's algorithm");

    // Add the new socket to readable sockets
    FD_SET(new_sock, &read_fds);
    // Update fdmax
    if (new_sock > fdmax)
        fdmax = new_sock;

    // Prepare to receive client ID
    memset(buffer, 0, BUFFLEN);
    ret = recv(new_sock, buffer, BUFFLEN, 0);
    DIE(ret < 0, "Error receiving client ID");

    string id(buffer);
    // Add client to vector, if it is not already there
    client *new_client = find_client_by_id(clients, id);
    if (new_client != NULL)
    {
        if (new_client->connected)
        {
            printf("Client %s already connected.\n", id.c_str());

            // Close connection
            FD_CLR(new_sock, &read_fds);
            close(new_sock);
        }
        else
        {
            // Reconnect client
            new_client->connected = true;
            new_client->socket = new_sock;
            printf("New client %s connected from %s:%hu.\n", new_client->id, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        }
    }
    else
    {
        // new client, add client to vector and set its fields
        client new_client;
        new_client.connected = true;
        strcpy(new_client.id, id.c_str());
        new_client.socket = new_sock;
        new_client.topics.clear();
        clients.push_back(new_client);
        printf("New client %s connected from %s:%hu.\n", new_client.id, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    }
}

void handle_client_socket(int i, vector<client> &clients, fd_set &read_fds, command_message &command_message)
{
    // receive command from subscriber
    int ret = recv(i, &command_message, sizeof(command_message), 0);
    DIE(ret < 0, "Error receiving command from subscriber");

    if (command_message.type == command_message.UNSUBSCRIBE)
    {
        // remove topic from client
        client *subscriber = find_client_by_socket(clients, i);
        if (subscriber != NULL)
        {
            subscriber->topics.erase(remove(subscriber->topics.begin(), subscriber->topics.end(), command_message.topic), subscriber->topics.end());
            printf("Unsubscribed from topic %s.\n", command_message.topic);

            // close connection
            FD_CLR(i, &read_fds);
            close(i);
        }
    }
    else if (command_message.type == command_message.SUBSCRIBE)
    {
        // add topic to new subscriber
        // find client by socket
        client *subscriber = find_client_by_socket(clients, i);
        if (subscriber != NULL)
        {
            subscriber->topics.push_back(command_message.topic);
            printf("Subscribed to topic %s.\n", command_message.topic);
        }
    }
    else if (command_message.type == command_message.EXIT)
    {
        client *subscriber = find_client_by_socket(clients, i);
        if (subscriber != NULL)
        {
            subscriber->connected = false;
            printf("Client %s disconnected.\n", subscriber->id);
        }

        // close connection
        FD_CLR(i, &read_fds);
        close(i);
    }
}

// main function to handle socket activity
void handle_socket_activity(int i, int udp_sock, int tcp_sock, vector<client> &clients, fd_set &read_fds, char *buffer, udp_message &udp_message, tcp_message &tcp_message, command_message &command_message, sockaddr_in &client_addr, int &fdmax)
{
    if (i == STDIN_FILENO)
    {
        handle_stdin(buffer, clients, udp_sock, tcp_sock, read_fds);
    }
    else if (i == tcp_sock)
    {
        handle_tcp_socket(i, clients, read_fds, buffer, client_addr, fdmax);
    }
    else if (i == udp_sock)
    {
        handle_udp_socket(i, clients, udp_message, tcp_message, client_addr);
    }
    else
    {
        handle_client_socket(i, clients, read_fds, command_message);
    }
}

// function to close all connections
void close_connections(vector<client> &clients, int udp_sock, int tcp_sock, fd_set read_fds)
{
    for (auto &client : clients)
    {
        if (client.connected)
        {
            if (FD_ISSET(client.socket, &read_fds))
            {
                FD_CLR(client.socket, &read_fds);
                close(client.socket);
            }
        }
    }
    close(udp_sock);
    close(tcp_sock);
}

int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, BUFSIZ);
    // open 2 sockets, one TCP one UDP on a port given as a parameter
    // the only command accepted from stdin is "exit"

    setvbuf(stdout, NULL, _IONBF, BUFSIZ);
    
    int port = atoi(argv[1]);
    DIE(port == 0, "Wrong port");

    int ret, udp_sock, tcp_sock;
    udp_message udp_message;
    tcp_message tcp_message;
    command_message command_message;
    vector<client> clients;
    // make sure the vector is empty
    clients.clear();

    sockaddr_in udp_addr, tcp_addr, client_addr;

    fd_set read_fds, tmp_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&tmp_fds);
    int fdmax;

    // open TCP socket
    tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    DIE(tcp_sock < 0, "TCP socket creation");

    // open UDP socket
    udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    DIE(udp_sock < 0, "UDP socket creation");

    // set server address for UDP
    memset((char *)&udp_addr, 0, sizeof(udp_addr));
    udp_addr.sin_family = AF_INET;
    udp_addr.sin_port = htons(port);
    udp_addr.sin_addr.s_addr = INADDR_ANY;

    // set server address for TCP
    memset((char *)&tcp_addr, 0, sizeof(tcp_addr));
    tcp_addr.sin_family = AF_INET;
    tcp_addr.sin_port = htons(port);
    tcp_addr.sin_addr.s_addr = INADDR_ANY;

    // bind UDP socket
    ret = bind(udp_sock, (sockaddr *)&udp_addr, sizeof(udp_addr));
    DIE(ret < 0, "UDP bind");

    // bind TCP socket
    ret = bind(tcp_sock, (sockaddr *)&tcp_addr, sizeof(tcp_addr));
    DIE(ret < 0, "TCP bind");

    // listen for TCP connections
    ret = listen(tcp_sock, 10);
    DIE(ret < 0, "TCP listen");

    // add sockets to read_fds
    FD_SET(udp_sock, &read_fds);
    FD_SET(tcp_sock, &read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    fdmax = max(udp_sock, tcp_sock);

    while (true)
    {
        tmp_fds = read_fds;

        ret = select(fdmax + 1, &tmp_fds, NULL, NULL, NULL);
        DIE(ret < 0, "Error combining file descriptors, multiplexing");

        char buffer[BUFFLEN];
        memset(buffer, 0, BUFFLEN);

        // check if stdin is set
        for (int i = 0; i <= fdmax; i++)
        {
            // iterate through all set sockets
            if (FD_ISSET(i, &tmp_fds))
            {
                handle_socket_activity(i, udp_sock, tcp_sock, clients, read_fds, buffer, udp_message, tcp_message, command_message, client_addr, fdmax);
            }
        }
    }
}


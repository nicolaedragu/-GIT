// one subscriber = one TCP socket
#include "utils.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, BUFSIZ);

    // first parameter is the ID_CLIENT (string max 10 ASCII chars)
    char id_client[11];
    strcpy(id_client, argv[1]);

    // second parameter is the IP_SERVER (dotted decimal)
    const char *ip_server = argv[2];

    // third parameter is the PORT_SERVER
    const char *port_server = argv[3];

    // at start, the client connects to the server with the ID given as a parameter
    // if a client with the same ID is already connected, server will print "Client <ID_CLIENT> already connected."

    // TCP clients can receive as commands from stdin:
    // "subscribe <TOPIC>"
    // "unsubscribe <TOPIC>"
    // "exit"
    // for every command given, client will print a line of feedback like so, AFTER the command is sent to the server:
    // "Subscribed to topic X"
    // "Unsubscribed from topic X"
    // X is the concrete value of topics of which the client subscribed/unsubscribed

    // for every message received from the server, the client will print the message in the following format:
    // <IP_CLIENT_UDP>:<PORT_CLIENT_UDP> - <TOPIC> - <TIP_DATE> - <VALOARE_MESAJ>

    // types of data: INT 0, SHORT_REAL 1, FLOAT 2, STRING 3
    // byte of sign will be 0 for positive numbers and 1 for negative numbers

    // if a client sends more messages in a short time, TCP can merge them
    
    char buf[sizeof(tcp_message)];
    char buffer[sizeof(tcp_message)];

    tcp_message tcp_message;
    command_message command_message;
    fd_set read_fds;
    fd_set tmp_fds;
    int ret;

    FD_ZERO(&tmp_fds);
    FD_ZERO(&read_fds);

    int socket_TCP = socket(AF_INET, SOCK_STREAM, 0);
    DIE(socket_TCP < 0, "TCP socket creation");

    int nagle = 1;
    ret = setsockopt(socket_TCP, IPPROTO_TCP, TCP_NODELAY, &nagle,
                     sizeof(int));
    DIE(ret < 0, "Error disabling Nagle's algorithm");

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(port_server));
    ret = inet_aton(ip_server, &server_addr.sin_addr);
    DIE(ret == 0, "Error setting the server IP");

    ret = connect(socket_TCP, (sockaddr *)&server_addr, sizeof(server_addr));
    DIE(ret < 0, "Error connecting to the server");

    ret = send(socket_TCP, id_client, strlen(id_client) + 1, 0);
    DIE(ret < 0, "Error sending the client ID");

    FD_SET(socket_TCP, &read_fds);
    FD_SET(STDIN_FILENO, &read_fds);

    while (true)
    {
        tmp_fds = read_fds;

        ret = select(socket_TCP + 1, &tmp_fds, NULL, NULL, NULL);
        DIE(ret < 0, "Error combining file descriptors, multiplexing");

        if (FD_ISSET(STDIN_FILENO, &tmp_fds))
        {
            memset(buffer, 0, BUFFLEN);
            fgets(buffer, BUFFLEN - 1, stdin);
            // remove the /n character from the end of the buffer
            
            if (strncmp(buffer, "exit", 4) == 0)
            {
                command_message.type = command_message.EXIT;

                ret = send(socket_TCP, &command_message,
                           sizeof(command_message), 0);
                DIE(ret < 0, "Error sending the exit command");

                break;
            }
            else if ((strncmp(buffer, "subscribe", 9) != 0) &&
                     (strncmp(buffer, "unsubscribe", 11) != 0))
            {
                perror("Invalid command.");
            }
            
            buffer[strlen(buffer) - 1] = '\0';
            char *topic = strtok(buffer, " ");
            if (strncmp(buffer, "subscribe", 9) == 0)
            {
                topic = strtok(NULL, " ");
                // remove the /n character from the end of the topic

                command_message.type = command_message.SUBSCRIBE;
                strcpy(command_message.topic, topic);

                ret = send(socket_TCP, &command_message,
                           sizeof(command_message), 0);
                DIE(ret < 0, "Error subscribing to the topic");

                printf("Subscribed to topic %s\n", topic);
            }
            else if (strncmp(buffer, "unsubscribe", 11) == 0)
            {
                topic = strtok(NULL, " ");
                // remove the /n character from the end of the topic

                command_message.type = command_message.UNSUBSCRIBE;
                strcpy(command_message.topic, topic);

                ret = send(socket_TCP, &command_message,
                           sizeof(command_message), 0);
                DIE(ret < 0, "Error unsubscribing from the topic");

                printf("Unsubscribed from topic %s\n", topic);
            }
        }

        if (FD_ISSET(socket_TCP, &tmp_fds))
        {
            memset(buf, 0, sizeof(tcp_message));
            // memset(&tcp_message, 0, sizeof(tcp_message));

            ret = recv(socket_TCP, buffer, sizeof(tcp_message), 0);
            DIE(ret < 0, "Error receiving the message");
            if (ret == 0)
            {
                break;
            }

            memcpy(&tcp_message, buffer, sizeof(tcp_message));
            // print like this:  [a_non_negative_int - INT - 10],
            printf("%s - %s - %f\n", tcp_message.topic, tcp_message.data_type, atof(tcp_message.contents));
        }
    }
    close(socket_TCP);
}

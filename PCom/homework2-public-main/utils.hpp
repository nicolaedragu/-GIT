#ifndef _UTILS_HPP
#define _UTILS_HPP

#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <queue>

#define DIE(assertion, call_description) \
    do { \
        if (assertion) { \
            fprintf(stderr, "(%s, %d): ", \
                    __FILE__, __LINE__); \
            perror(call_description); \
            exit(errno); \
        } \
    } while (0)
    
#define BUFFLEN 1552
    
// structura de mesaje subscriber comanda
typedef struct {
    enum {
        EXIT = 0,
        SUBSCRIBE = 1,
        UNSUBSCRIBE = 2,
    } type;
    char topic[51];
} command_message;
    
// structura de mesaje peste TCP server -> subscriber
typedef struct {
    char ip_client[16];
    int port_client;
    char topic[51];
    char data_type[11];
    char contents[1501];
} tcp_message;
    
// structura de mesaje peste UDP client -> client (readable)
typedef struct {
    char topic[51];
    int data_type;
    char contents[1501];
} udp_message;
    
// structura client
typedef struct {
    char id[11];
    int socket;
    std::vector<std::string> topics;
    bool connected;
} client;

#endif
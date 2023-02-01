#ifndef FT_SHIELD_MAIN_H
#define FT_SHIELD_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#if defined(_WIN32) || defined(WIN32)

#include <winsock2.h>
#include <ws2tcpip.h>

typedef SOCKET socket_t;
#define CLOSE_SOCKET closesocket

#elif defined(__linux__)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

typedef int socket_t;
#define CLOSE_SOCKET close
#endif

#define PORT 4242

typedef struct s l_socket;
struct s {
    int socket_fd;
    l_socket* next;
    char is_listen;
    char auth;
};

typedef struct connection {
    int max_fd;
    socklen_t clilen;
    struct sockaddr_in serv_addr;
    l_socket* list_socket;
} s_connection;

#endif //FT_SHIELD_MAIN_H

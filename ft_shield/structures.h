#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "main.h"

typedef struct {
    int sockfd;
    int newsockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    FILE *shell;
} s_connection;

#endif //STRUCTURES_H

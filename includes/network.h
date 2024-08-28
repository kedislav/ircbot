#pragma once
#include "util.h"

typedef struct connection {
    struct sockaddr_in addr;
    struct hostent* host;
    int fd;
} connection_t;

connection_t *create_connection();
int conn_connect(connection_t *conn);
void conn_send(connection_t *conn, char* command);
void reg(connection_t* conn, const char* nick, const char* user, const char* channel);
int send_data(int sockfd, const char* data);
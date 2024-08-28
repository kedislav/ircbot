#pragma once
#include "util.h"

int send_data(int sockfd, const char* data);
int reg(int sockfd, const char* nick, const char* user, const char* channel);


typedef struct connection {
    struct sockaddr_in addr;
    struct hostent* host;
    int fd;
} connection_t;

connection_t *create_connection();
int conn_connect(connection_t *conn);
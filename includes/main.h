#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

/*---------[ MACROS ]---------*/
#define SERVER "Irc.oftc.net"
#define PORT 6697
#define INIT_BUFF 256

#define ERR(msg, ...) fprintf(stderr, "[!] " msg "\n", ##__VA_ARGS__)
#define LOG(msg, ...) printf("[+] " msg "\n", ##__VA_ARGS__)

/*---------[ PROTOTYPES ]---------*/
int send_data(int sockfd, const char* data);
int reg(int sockfd, const char* nick, const char* user, const char* channel);

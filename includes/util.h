#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif
#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif

#define SERVER "Irc.oftc.net"
#define PORT 6697
#define INIT_BUFF 256
#define BUF_SIZE 1024
#define true 1
#define false 0

#define ERR(msg, ...) fprintf(stderr, "[!] " msg "\n", ##__VA_ARGS__)
#define LOG(msg, ...) printf("[+] " msg "\n", ##__VA_ARGS__)

char* format(char* fmt, ...);
typedef unsigned int uint_t;
typedef unsigned int bool_t;
bool_t __empty(char* string);
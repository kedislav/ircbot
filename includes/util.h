#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SERVER "Irc.oftc.net"
#define PORT 6697
#define INIT_BUFF 256

#define ERR(msg, ...) fprintf(stderr, "[!] " msg "\n", ##__VA_ARGS__)
#define LOG(msg, ...) printf("[+] " msg "\n", ##__VA_ARGS__)

char* format(char* fmt, ...);
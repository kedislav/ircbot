#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
/*---------[ MACROS ]---------*/
#define SERVER "Irc.oftc.net"
#define PORT 6697
#define INIT_BUFF 256

#define ERR(msg, ...) fprintf(stderr, "[!] " msg "\n", ##__VA_ARGS__)
#define LOG(msg, ...) printf("[+] " msg "\n", ##__VA_ARGS__)

/*---------[ PROTOTYPES ]---------*/
int send_data(int sockfd, const char* fmt);
int reg(int sockfd, const char* nick, const char* user, const char* channel);

int main(void) {
  /*---------[ VARIABLES ]---------*/
  int ret = 0;
  int sockfd = 0;
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  char* command = "PRIVMSG #solrun-test : PETAK JE VECE; SEDAM U MECE\r\n";

  // create a socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    ERR("Failed to create socket.");
    close(sockfd);
    exit(EXIT_FAILURE);
  }
  LOG("Created socket");

  // config server address
  ret = inet_pton(AF_INET, SERVER, &server_addr.sin_addr);
  if (ret <= 0) {
    ERR("Invalid address or address not supported");
    close(sockfd);
    exit(EXIT_FAILURE);
  }
  LOG("Configured servers address");
  
  // connect to server
  ret = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if (ret <= 0) {
    ERR("Failed to connect to server");
    close(sockfd);
    exit(EXIT_FAILURE);
  }
  LOG("Connected to server successfully!");

  ret = reg(sockfd, "ircbot", "kedbot-3000", "#solrun-test");
  if (ret == 1) {
    ERR("Failed to register on IRC Server");
    close(sockfd);
    exit(EXIT_FAILURE);
  }
  LOG("Sucessfully registered on IRC Server");
  send_data(sockfd, command);
  if (ret == 1) {
    ERR("Failed to send a message to server");
    close(sockfd);
    exit(EXIT_FAILURE);
  }
  LOG("Sent a message to the server");

  LOG("Press any button to close connection.");
  getchar();
  close(sockfd);
  return 0;
}

int send_data(int sockfd, const char* data) {
  /*---------[ VARIABLES ]---------*/
  int   ret     = 0;
  int   written = 0;

  ret = send(sockfd, data, written, 0);
  if (ret < 0) {
    ERR("sending data to server failed");
    return 1;
  }
  
  return 0;
}

int reg(int sockfd, const char* nick, const char* user, const char* channel) {
  /*---------[ VARIABLES ]---------*/
  int ret = 0;
  size_t len = strlen("NICK ") + strlen(nick) + strlen("\r\n");
  char* buffer = (char*)malloc(len+1);
  if (buffer == NULL) {
    ERR("Failed to allocate memory to register");
    return 1;
  }
  
  snprintf(buffer, len+1, "NICK %s\r\n", nick);
  ret = send_data(sockfd, buffer);
  if (ret == 1) {
    ERR("(nick) failed to send data to server");
    free(buffer);
    return 1;
  }
  
  len = strlen("USER ") + strlen(user) + strlen(" 0 * :robot\r\n"); // robot is realname
  buffer = (char*)realloc(buffer, len+1);
  if (buffer == NULL) {
    ERR("Failed to reallocate memory to register");
    return 1;
  }
  snprintf(buffer, len+1, "USER %s 0 * :robot\r\n", nick);
  ret = send_data(sockfd, buffer);
  if (ret == 1) {
    ERR("(user) failed to send data to server");
    free(buffer);
    return 1;
  }

  len = strlen("JOIN ") + strlen(channel) + strlen("\r\n");
  buffer = (char*)realloc(buffer, len+1);
  if (buffer == NULL) {
    ERR("Failed to reallocate memory to register");
    return 1;
  }
  snprintf(buffer, len+1, "JOIN %s\r\n", channel);
  ret = send_data(sockfd, buffer);
  if (ret == 1) {
    ERR("(chan) failed to send data to server");
    return 1;
  }

  free(buffer);
  return 0;
}


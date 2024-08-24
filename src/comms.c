#include "../includes/main.h"

int send_data(int sockfd, const char* data) {
  /*---------[ VARIABLES ]---------*/
  int total_sent = 0;
  int len = strlen(data);

  while (total_sent < len) {
    // could maybe cause problems
    // but essentially makes sure it sends all of the data over
    int ret = send(sockfd, data + total_sent, len - total_sent, 0);
    if (ret < 0) {
      ERR("Sending data to server failed");
      return 1;
    }
    total_sent += ret;
  }

  return 0;
}

// registers ya on the IRC server
int reg(int sockfd, const char* nick, const char* user, const char* channel) {
  /*---------[ VARIABLES ]---------*/
  int     ret = 0;
  size_t  len = 0;
  char* buffer;
  char* tmp;
 
  // check how long the string is gonna be
  len = strlen("NICK ") + strlen(nick) + strlen("\r\n");
  // allocate memory for our string (+1 because 0 byte)
  buffer = (char*)malloc(len + 1);
  if (buffer == NULL) {
    ERR("Failed to allocate memory to register");
    return 1;
  }
  
  // assemble our string 
  snprintf(buffer, len + 1, "NICK %s\r\n", nick);
  // send the data over
  ret = send_data(sockfd, buffer);
  if (ret == 1) {
    ERR("(nick) Failed to send data to server");
    free(buffer);
    return 1;
  }

  // repeat process
  len = strlen("USER ") + strlen(user) + strlen(" 0 * :robot\r\n");
  // just here we resize our buffer so the new string fits
  tmp = realloc(buffer, len + 1);
  if (tmp == NULL) {
    ERR("Failed to reallocate memory to register");
    free(buffer);
    return 1;
  }
  buffer = tmp;

  snprintf(buffer, len + 1, "USER %s 0 * :robot\r\n", user);
  ret = send_data(sockfd, buffer);
  if (ret == 1) {
    ERR("(user) Failed to send data to server");
    free(buffer);
    return 1;
  }

  len = strlen("JOIN ") + strlen(channel) + strlen("\r\n");
  tmp = realloc(buffer, len + 1);
  if (tmp == NULL) {
    ERR("Failed to reallocate memory to register");
    free(buffer);
    return 1;
  }
  buffer = tmp;

  snprintf(buffer, len + 1, "JOIN %s\r\n", channel);
  ret = send_data(sockfd, buffer);
  if (ret == 1) {
    ERR("(chan) Failed to send data to server");
    free(buffer);
    return 1;
  }

  // IMPORTANT free the memory!!
  free(buffer);
  return 0;
}

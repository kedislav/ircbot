#include "../includes/network.h"
#include "../includes/util.h"

int send_data(int sockfd, const char* data) {
  /*---------[ VARIABLES ]---------*/
  int total_sent = 0;
  int len = strlen(data);

  while (total_sent < len) {
    // could maybe cause problems
    // but essentially makes sure it sends all of the data over
    ssize_t ret = send(sockfd, data + total_sent, len - total_sent, 0);
    if (ret < 0) {
      ERR("Sending data to server failed with code %zd", ret);
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
  char* buf;
  char* tmp;
 
  // check how long the string is gonna be
  len = strlen("NICK ") + strlen(nick) + strlen("\r\n");
  // allocate memory for our string (+1 because 0 byte)
  buf = (char*)malloc(len + 1);
  if (buf == NULL) {
    ERR("Failed to allocate memory to register %p", buf);
    return 1;
  }
  
  // assemble our string 
  snprintf(buf, len + 1, "NICK %s\r\n", nick);
  // send the data over
  ret = send_data(sockfd, buf);
  if (ret == 1) {
    ERR("(nick) Failed to send data to server with code %d", ret);
    free(buf);
    return 1;
  }

  // repeat process
  len = strlen("USER ") + strlen(user) + strlen(" 0 * :robot\r\n");
  // just here we resize our buffer so the new string fits
  tmp = realloc(buf, len + 1);
  if (tmp == NULL) {
    ERR("Failed to reallocate memory to register %p", tmp);
    free(buf);
    return 1;
  }
  buf = tmp;

  snprintf(buf, len + 1, "USER %s 0 * :robot\r\n", user);
  ret = send_data(sockfd, buf);
  if (ret == 1) {
    ERR("(user) Failed to send data to server with code %d", ret);
    free(buf);
    return 1;
  }

  len = strlen("JOIN ") + strlen(channel) + strlen("\r\n");
  tmp = realloc(buf, len + 1);
  if (tmp == NULL) {
    ERR("Failed to reallocate memory to register %p", tmp);
    free(buf);
    return 1;
  }
  buf = tmp;

  snprintf(buf, len + 1, "JOIN %s\r\n", channel);
  ret = send_data(sockfd, buf);
  if (ret == 1) {
    ERR("(chan) Failed to send data to server with code %d", ret);
    free(buf);
    return 1;
  }

  // IMPORTANT free the memory!!
  free(buf);
  return 0;
}

connection_t *create_connection() {
  struct hostent* host = gethostbyname(SERVER);
  struct sockaddr_in addr;
  connection_t *conn = (connection_t*) malloc(sizeof(connection_t));

  if (host == NULL) {
    ERR("Failed to resolve hostname %p", host);
    exit(EXIT_FAILURE);
  }
  // configure server address
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  memcpy(&addr.sin_addr, host->h_addr, host->h_length);
  conn->addr = addr;
  conn->host = host;
  conn->fd = socket(AF_INET, SOCK_STREAM, 0);
  if (conn->fd < 0) {
    ERR("Failed to create socket, %d", conn->fd);
    exit(EXIT_FAILURE);
  }
  return conn;
}
int conn_connect(connection_t *conn) { return connect(conn->fd, (struct sockaddr*)&conn->addr, sizeof(conn->addr)); }
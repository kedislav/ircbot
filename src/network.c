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
void reg(connection_t *conn, const char* nick, const char* user, const char* channel) {
  conn_send(conn, format("NICK %s\r\n", nick));
  conn_send(conn, format("USER %s 0 * :robot\r\n", user));
  conn_send(conn, format("JOIN %s\r\n", channel));
}

void conn_send(connection_t *conn, char* command) {
  size_t len = strlen(command);
  char* buf = (char*)malloc(sizeof(char) * len);
  if (!buf) {
    ERR("Failed to allocate buffer %p, (L: %zd | C: %s)", buf, len, command);
    exit(EXIT_FAILURE);
  }
  snprintf(buf, len + 1, command);
  int ret = send_data(conn->fd, buf);
  if (ret != 0) {
    ERR("Failed to send %s (Code %d)", command, ret);
    exit(EXIT_FAILURE);
  }
  free(buf);
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
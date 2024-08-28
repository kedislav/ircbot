#include "../includes/network.h"
#include "../includes/util.h"

int main(void) {
  /*---------[ VARIABLES ]---------*/
  int ret = 0;
  char* command = "PRIVMSG #solrun-test : PETAK JE VECE; SEDAM U MECE\r\n";
  connection_t *conn = create_connection();
  // connect to the server
  if (conn_connect(conn) < 0) {
    ERR("Failed to connect to server %d", ret);
    close(conn->fd);
    exit(EXIT_FAILURE);
  }
  LOG("Connected to server successfully!");

  // register on IRC server
  reg(conn, "ircbot", "kedbot-3000", "#solrun-test");
  LOG("Successfully registered on IRC Server");

  // send message to the server
  ret = send_data(conn->fd, command);
  if (ret == 1) {
    ERR("Failed to send a message to server with code %d", ret);
    close(conn->fd);
    exit(EXIT_FAILURE);
  }
  LOG("Sent a message to the server");

  LOG("Press any button to close connection.");
  getchar();
  close(conn->fd);
  return 0;
}


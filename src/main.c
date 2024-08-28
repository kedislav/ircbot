#include "../includes/network.h"
#include "../includes/util.h"
#define NICK "ircbot"
#define USER "kedbot-300"
#define CHAN "#solrun-test"

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
  LOG("Connected to server successfully! %d", conn->fd);

  // register on IRC server
  reg(conn, NICK, USER, CHAN);
  LOG("Successfully registered %s as %s on %s", USER, NICK, CHAN);

  // send message to the server
  ret = send_data(conn->fd, command);
  if (ret == 1) {
    ERR("Failed to send a message to server with code %d", ret);
    close(conn->fd);
    exit(EXIT_FAILURE);
  }
  LOG("Sent %s to the server", command);

  printf("Listening ... (anykey)");
  getchar();
  close(conn->fd);
  return 0;
}


#include "../includes/main.h"

int main(void) {
  /*---------[ VARIABLES ]---------*/
  int ret = 0;
  int sockfd = 0;
  struct sockaddr_in server_addr;
  char* command = "PRIVMSG #solrun-test : PETAK JE VECE; SEDAM U MECE\r\n";

  // get IP address
  struct hostent* host = gethostbyname(SERVER);
  if (host == NULL) {
    ERR("Failed to resolve hostname.");
    exit(EXIT_FAILURE);
  }
  
  // create a socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    ERR("Failed to create socket.");
    exit(EXIT_FAILURE);
  }
  LOG("Created socket");

  // configure server address
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  memcpy(&server_addr.sin_addr, host->h_addr, host->h_length);

  // connect to the server
  ret = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if (ret < 0) {
    ERR("Failed to connect to server");
    close(sockfd);
    exit(EXIT_FAILURE);
  }
  LOG("Connected to server successfully!");

  // register on IRC server
  ret = reg(sockfd, "ircbot", "kedbot-3000", "#solrun-test");
  if (ret == 1) {
    ERR("Failed to register on IRC Server");
    close(sockfd);
    exit(EXIT_FAILURE);
  }
  LOG("Successfully registered on IRC Server");

  // send message to the server
  ret = send_data(sockfd, command);
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


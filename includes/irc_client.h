#ifndef IRC_CLIENT_H
#define IRC_CLIENT_H

#include <stdio.h>

// IRC_CLIENT_H
// This header file:
//    a) Declares a structure called "irc_t" (for irc type) that holds
//       variables that serve as buffers, to better parse and manage
//       data, memory and connections.
//
//    b) Sets up functions related to the IRC protocol to be in
//       standard with the RFC1459, specially when it comes to
//       client functions that the bot should be able to perform
//
//    c) And finally declares functions that serve as buffer updaters
//       for the "irc_t" struct, which will then be passed to the
//       "original" irc functions to be enacted, providing better
//       handling of memory and error checking.

// irc_t
typedef struct {
  int sock;          // socket descriptor
  FILE *file;        // file pointer for logs or configs
  char channel[256]; // irc channel
  char *nick;        // nickname
  char servbuf[512]; // server data buffer
  int bufptr;        // pointer to said buffer
} irc_t;

// IRC Protocol Actions - See: https://www.rfc-editor.org/rfc/rfc1459
//>>> 4.1 Connection Registration
int irc_reg(int sock, const char *nick, const char *username,
            const char *fullname);
int irc_quit(int sock, const char *quit_msg);
int irc_nick(int sock, const char *nick);
//>>> 4.2 Channel Operations
int irc_join(int sock, const char *channel);
int irc_part(int sock, const char *data);
int irc_topic(int sock, const char *channel, const char *data);
int irc_action(int sock, const char *channel, const char *data);
//>>> 4.4 Sending Messages
int irc_privmsg(int sock, const char *user, const char *data);
int irc_msg(int sock, const char *channel, const char *data);
//>>> 4.6 Miscellaneous
int irc_pong(int sock, const char *pong);

// Functions and Buffer Updaters
int irc_handle_data(irc_t *irc_client);
int irc_parse_action(irc_t *irc_client);
int irc_connect(irc_t *irc_client, const char *server, const char *port);
int irc_login(irc_t *irc_client, const char *nick);
int irc_join_channel(irc_t *irc_client, const char *channel);
int irc_leave_channel(irc_t *irc_client);
int irc_reply_message(irc_t *irc_client, char *nick, char *msg);
int irc_set_output(irc_t *irc_client, const char *file);
int irc_log_message(irc_t *irc_client, const char *nick, const char *msg);
void irc_close(irc_t *irc_client);

#endif

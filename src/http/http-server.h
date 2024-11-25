#ifndef _HTTP_SERVER_
#define _HTTP_SERVER_

#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "server-config.h"

#define BUFFER_SIZE 16000

typedef struct
{
  int socket;
  struct sockaddr_in address;
} http_server;

typedef struct
{
  int socket;
  struct sockaddr_in address;
} http_client;

http_server* create_server(server_config *config);

http_client* accept_client(http_server *server);

void destroy_server(http_server *server);

void destroy_client(http_client *client);


#endif

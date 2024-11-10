#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "server-config.c"

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

http_server* create_server(server_config *config)
{
  http_server *server = (http_server *)malloc(sizeof(http_server));
  int socket_option = 1;

  // address
  server->address.sin_family = AF_INET;
  server->address.sin_addr.s_addr = INADDR_ANY;
  server->address.sin_port = htons(config->port);
  socklen_t address_length = sizeof(server->address);

  // create socket
  if ((server->socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    perror("Creating socket failed");
    exit(EXIT_FAILURE);
  }

  // setsockopt
  if (setsockopt(server->socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &socket_option, sizeof(socket_option)))
  {
    perror("setsockopt failed");
    exit(EXIT_FAILURE);
  }

  // bind server socket to address and port
  if (bind(server->socket, (struct sockaddr*)&server->address, address_length) < 0)
  {
    perror("Binding socket failed");
    exit(EXIT_FAILURE);
  }

  return server;
}

http_client* accept_client(http_server *server)
{
  http_client *client = (http_client *)malloc(sizeof(http_client));

  client->address.sin_family = AF_INET;
  client->address.sin_addr.s_addr = INADDR_ANY;
  socklen_t address_length = sizeof(client->address);

  if ((client->socket = accept(server->socket, (struct sockaddr*)&client->address, &address_length)) < 0)
  {
    perror("Couldn\'t accept connection");
  }

  // get IP
  // char *ip;
  // inet_ntop(AF_INET, &address->sin_addr, ip, INET_ADDRSTRLEN);

  return client;
}

void destroy_server(http_server *server)
{
  close(server->socket);
  free(server);
}

void destroy_client(http_client *client)
{
  close(client->socket);
  free(client);
}

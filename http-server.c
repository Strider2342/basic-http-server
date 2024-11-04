#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct
{
  int socket;
  struct sockaddr_in address;
  socklen_t address_length;
} http_server;

typedef struct
{
  int socket;
} http_client;

http_server* create_server(int port)
{
  http_server *server = (http_server *)malloc(sizeof(http_server));
  int socket_option = 1;

  // address
  server->address.sin_family = AF_INET;
  server->address.sin_addr.s_addr = INADDR_ANY;
  server->address.sin_port = htons(port);
  server->address_length = sizeof(server->address);

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
  if (bind(server->socket, (struct sockaddr*)&server->address, server->address_length) < 0)
  {
    perror("Binding socket failed");
    exit(EXIT_FAILURE);
  }

  return server;
}

http_client* accept_client(http_server *server)
{
  http_client *client = (http_client *)malloc(sizeof(http_client));

  if ((client->socket = accept(server->socket, (struct sockaddr*)&server->address, &server->address_length)) < 0)
  {
    perror("Couldn\'t accept connection");
  }

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

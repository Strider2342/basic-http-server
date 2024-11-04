#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "http-server.c"
#include "http-response.c"

int main()
{
  http_server *server = create_server(1234);

  // listening
  if (listen(server->socket, 3) < 0)
  {
    perror("Failed to start listening");
    exit(EXIT_FAILURE);
  }

  while (1)
  {
    http_client *client = accept_client(server);

    char *response = create_response();

    send(client->socket, response, strlen(response), 0);

    destroy_client(client);
  }

  destroy_server(server);

  return 0;
}

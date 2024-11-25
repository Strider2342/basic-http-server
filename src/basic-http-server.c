#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "http/server-config.h"
#include "http/http-server.h"
#include "http/http-request.h"
#include "http/http-response.h"

int main()
{
  server_config *config = (server_config *)malloc(sizeof(server_config));
  config->port = 1234;
  config->static_dir = "./public";

  http_server *server = create_server(config);

  // listening
  if (listen(server->socket, 3) < 0)
  {
    perror("Failed to start listening");
    exit(EXIT_FAILURE);
  }

  while (1)
  {
    http_client *client = accept_client(server);

    // parse request
    char buffer[BUFFER_SIZE] = "";
    ssize_t bytes_read = read(client->socket, buffer, BUFFER_SIZE - 1);

    http_request *request = parse_http_request(buffer);
    print_request(request);

    // create response
    char *response = build_response(request, config);

    send(client->socket, response, strlen(response), 0);

    free(request);
    free(response);
    destroy_client(client);
  }

  destroy_server(server);
  free(config);

  return 0;
}

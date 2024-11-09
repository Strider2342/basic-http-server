#include "string-util.c"

#define DEFAULT_MIME_TYPE "application/octet-stream"

typedef struct
{
  char *method;
  char *url;
  char *http_version;
  char *headers[10]; // supports 10 headers for now
} http_request;

http_request* parse_http_request(char *original_request_buffer);

http_request* parse_http_request(char *original_request_buffer)
{
  http_request *request = (http_request *)malloc(sizeof(http_request));

  size_t buffer_length = strlen(original_request_buffer);

  char request_buffer[buffer_length];
  strncpy(request_buffer, original_request_buffer, buffer_length + 1); // TODo: why

  char *first_line = strtok(request_buffer, "\n");
  request->method = strtok(first_line, " ");
  request->url = strtok(NULL, " ");
  request->http_version = strtok(NULL, " ");

  return request;
}

void print_request(http_request *request)
{
  printf("method: %s\n", request->method);
  printf("url: %s\n", request->url);
  printf("version: %s\n", request->http_version);
}

#ifndef _HTTP_REQUEST_
#define _HTTP_REQUEST_

#define DEFAULT_MIME_TYPE "application/octet-stream"

typedef struct
{
  char *method;
  char *url;
  char *http_version;
  char *headers[10]; // supports 10 headers for now
} http_request;

http_request* parse_http_request(char *original_request_buffer);

void print_request(http_request *request);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http-request.h"
#include "http-response.h"
#include "util/string-util.h"
#include "os/file-system-util.h"

char* determine_mime_type(char *url)
{
  char *ext = strrchr(url, '.');

  if (ext == NULL)
  {
    return DEFAULT_MIME_TYPE;
  }

  ext++;
  to_lower_case(ext);

  // TODO: this should be a hash table?
  if (strcmp(ext, "html") == 0 || strcmp(ext, "htm") == 0)
  {
    return "text/html";
  }

  if (strcmp(ext, "css") == 0)
  {
    return "text/css";
  }

  if (strcmp(ext, "ico") == 0)
  {
    return "image/x-icon";
  }

  if (strcmp(ext, "js") == 0)
  {
    return "application/javascript";
  }

  if (strcmp(ext, "json") == 0)
  {
    return "application/json";
  }

  if (strcmp(ext, "txt") == 0)
  {
    return "text/plain";
  }

  if (strcmp(ext, "gif") == 0)
  {
    return "image/gif";
  }

  if (strcmp(ext, "jpeg") == 0 || strcmp(ext, "jpg") == 0)
  {
    return "image/jpg";
  }

  if (strcmp(ext, "png") == 0)
  {
    return "image/png";
  }

  // TODO: support more MIME types

  return DEFAULT_MIME_TYPE;
}

char* set_header(char *headers, char *name, char *value)
{
  char *new_headers = (char*)malloc(strlen(headers) + strlen(name) + strlen(value) + 6);

  strcpy(new_headers, headers);
  strcat(new_headers, name);
  strcat(new_headers, ": ");
  strcat(new_headers, value);
  strcat(new_headers, ";\r\n");

  return new_headers;
}

char* get_status_line(int status_code)
{
  switch (status_code)
  {
    case 200: return "HTTP/1.1 200 OK\r\n";
    case 401: return "HTTP/1.1 401 Unauthorized\r\n";
    case 403: return "HTTP/1.1 403 Forbidden\r\n";
    case 404: return "HTTP/1.1 404 Not found\r\n";
    default:  return "HTTP/1.1 418 I\'m a teapot\r\n";
  }
}

char* build_response(http_request *request, server_config *config)
{
  char *status, *headers, *content = "";
  char *file_name;

  // routing
  if (strcmp(request->url, "/") == 0)
  {
    file_name = (char*)malloc(strlen(config->static_dir) + strlen("/index.html") + 1);
    strcpy(file_name, config->static_dir);
    strcat(file_name, "/index.html");
  }
  else
  {
    file_name = (char*)malloc(strlen(config->static_dir) + strlen(request->url) + 1);
    strcpy(file_name, config->static_dir);
    strcat(file_name, request->url);
  }

  // load file
  load_file_result *result = load_file(file_name);

  if (result->error == NULL)
  {
    content = result->content;
    status = get_status_line(200);

    headers = "charset=UTF-8;\n";
    headers = set_header(headers, "Content-Type", determine_mime_type(file_name));
  }
  else
  {
    // TODO: error handling
    status = get_status_line(404);
    headers = "charset=UTF-8;\n";
  }

  size_t response_size = strlen(status) + strlen(headers) + 1 + strlen(content) + 1;
  char *response = (char*)malloc(response_size);

  strcpy(response, status);
  strcat(response, headers);
  strcat(response, "\r\n");
  strcat(response, content);

  free(result);
  free(file_name);

  return response;
}

char* create_hello_world_response()
{
  char *status, *headers, *content;

  status = get_status_line(200);

  headers = "Content-Type: text/html\r\n\r\n";

  content = "<!DOCTYPE html>\r\n"
            "<html>\r\n"
            "  <head></head>\r\n"
            "  <body>\r\n"
            "    Hello, World!\r\n"
            "  </body>\r\n"
            "</html>\r\n";

  size_t response_size = strlen(status) + strlen(headers) + strlen(content);
  char *response = (char*)malloc(response_size);

  strcpy(response, status);
  strcat(response, headers);
  strcat(response, content);

  return response;
}

#ifndef _HTTP_RESPONSE_
#define _HTTP_RESPONSE_

#include "server-config.h"
#include "http-request.h"

char* determine_mime_type(char *url);
char* set_header(char *headers, char *name, char *value);
char* get_status_line(int status_code);
char* build_response(http_request *request, server_config *config);
char* create_hello_world_response();

#endif

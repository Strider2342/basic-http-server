#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* load_html()
{
  FILE *file = fopen("./public/index.html", "r");

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *content = (char*)malloc(file_size + 1);
  if (content == NULL)
  {
    perror("Failed to allocate memory");
    fclose(file);
    exit(EXIT_FAILURE);
  }

  fread(content, 1, file_size, file);
  content[file_size] = '\0';

  fclose(file);

  return content;
}

char* create_response()
{
  char *headers = "HTTP/1.1 200 OK\n"
                  "Content-Type: text/html; charset=UTF-8\n\n";
  char *html = load_html();

  size_t response_size = strlen(headers) + strlen(html) + 1;
  char *response = (char*)malloc(response_size);

  strcpy(response, headers);
  strcat(response, html);

  free(html);

  return response;
}

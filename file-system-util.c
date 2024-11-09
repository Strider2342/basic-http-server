#include <stdio.h>

typedef struct
{
  char *content;
  char *error;
} load_file_result;

load_file_result* load_file(char *file_path);

load_file_result* load_file(char *file_path)
{
  FILE *file = fopen(file_path, "r");

  load_file_result *result = (load_file_result *)malloc(sizeof(load_file_result));

  if (file == NULL)
  {
    result->content = NULL;
    result->error = "Couldn\'t open file";
    return result;
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  result->content = (char*)malloc(file_size + 1);
  if (result->content == NULL)
  {
    perror("Failed to allocate memory");
    fclose(file);
    exit(EXIT_FAILURE);
  }

  fread(result->content, 1, file_size, file);
  result->content[file_size] = '\0';

  result->error = NULL;

  fclose(file);

  return result;
}

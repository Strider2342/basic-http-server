#ifndef _FILE_SYSTEM_UTIL_
#define _FILE_SYSTEM_UTIL_

typedef struct
{
  char *content;
  char *error;
} load_file_result;

load_file_result* load_file(char *file_path);

#endif

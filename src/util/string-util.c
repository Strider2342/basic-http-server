#include <ctype.h>
#include <string.h>
#include "string-util.h"

void to_lower_case(char *str)
{
  for (char *c = str; *c != '\0'; c++)
  {
    *c = tolower(*c);
  }
}

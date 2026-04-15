#include <stdlib.h>
#include <stdio.h>
#include "db_helper.h"


char *allocate_string(int len) {
  char *str = malloc(len * sizeof(char) + sizeof(char));
  if (str == NULL) {
    fprintf(stderr, "Unable to allocate memory for a string in allocate string. Suggest saving and quitting\n");
    return NULL;
  }
  return str;
}
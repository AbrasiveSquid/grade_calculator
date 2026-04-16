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

int validate_integer(int min, int max) {
  int num;
  char term;
  while (1) {
    printf("Enter an integer between %d - %d\n", min, max);

    if(scanf("%d%c", &num, &term) != 2  && is_valid_input(num, term, min, max))
      return num;
    else 
      printf("Invalid input, enter an int followed by enter/return key\n");
  }
}

bool is_valid_input(int num, char term, int min, int max) {
  if (term != '\n')
    return false;
  if (num < min || num > max)
    return false;
  return true;


}

/* Header file for the helper functions needed by the database*/
#ifndef DB_HELPER__H
#define DB_HELPER__H
#include "DB.h"
#include <stdbool.h>



/* allocates memory on the heap for a string of size len. Len does not include null char
But memory is allocated to include the null char

Parameters:
  len:int, length of the string
  
Returns: 
  Pointer for the string
*/
char *allocate_string(int len);

/* validate integer was entered by the user*/
int validate_integer(int min, int max);

/* validates that input from user was entered correctly*/
bool is_valid_input(int num, char term, int min, int max);


#endif
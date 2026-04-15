/* Header file for the helper functions needed by the database*/
#ifndef DB_HELPER__H
#define DB_HELPER__H
#include "DB.h"


/* allocates memory on the heap for a string of size len. Len does not include null char
But memory is allocated to include the null char

Parameters:
  len:int, length of the string
  
Returns: 
  Pointer for the string
*/
char *allocate_string(int len);


#endif
/* Header file for the helper functions needed by the database*/
#ifndef DB_HELPER__H
#define DB_HELPER__H
#include "DB.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>



/* allocates memory on the heap for a string of size len. Len does not include null char
But memory is allocated to include the null char

Parameters:
  len:int, length of the string

Returns:
  Pointer for the string
*/
char *allocate_string(int len);

/* gets a valid integer from the user*/
int get_valid_integer(int min, int max);

/* validates that input from user was entered correctly */
bool is_valid_input(int num, char term, int min, int max);

/* compares two strings to check if they are same value, not case sensitive */
bool strcmp_case_insensitive(const char *str1, const char *str2);

/* checks if a course exists in the database already */
bool course_exists(char *course_name);

/* resizes the database by 50% */
int db_resize(void);


#endif

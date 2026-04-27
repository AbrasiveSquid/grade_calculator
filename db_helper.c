
#include "db_helper.h"


char *allocate_string(int len) {
  char *str = malloc(len * sizeof(char) + sizeof(char));
  if (str == NULL) {
    fprintf(stderr, "Unable to allocate memory for a string in allocate string. Suggest saving and quitting\n");
    return NULL;
  }
  return str;
}

int get_valid_integer(int min, int max) {
  int num;
  char term;
  char input_buff[5];
  while (1) {
    printf("Enter an integer between %d - %d\n", min, max);
    fgets(input_buff, 4, stdin);

    if(sscanf(input_buff,"%d%c", &num, &term) == 2  && is_valid_input(num, term, min, max))
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


bool strcmp_case_insensitive(const char *str1, const char *str2) {
  int comp;
  while (*str1 != '\0' || *str2 != '\0')
    {
      comp = tolower((unsigned char) *str1) - tolower((unsigned char) *str2);
      str1++,str2++;
      if (comp != 0)
        return false;
    }

  return true;
}


bool course_exists(char *course_name) {
  if ((strlen(course_name)) < 1)
    return true;

  for (int i = 0; i < DB->courseCount; i++) {
    if (strcmp_case_insensitive(DB->courses[i]->course_name, course_name))
      return true;
  }
  return false;
}


int db_resize(void) {
  Course **tempDB;
  int new_capacity = (int)DB->courseCap * 1.5;
  tempDB = realloc(DB->courses, sizeof(*tempDB) *new_capacity);
  if (tempDB == NULL) {
    fprintf(stderr, "Failed to resize Database, save now and exit\n");
    return 0;
  }

  DB->courses = tempDB;
  DB->courseCap = new_capacity;
  return 1;
}

bool is_printable_char(int ch) {
  if (ch > 31 && ch < 127)
    return true;
  return false;
}


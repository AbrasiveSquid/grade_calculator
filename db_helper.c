
#include "db_helper.h"
#include "DB.h"


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

float get_valid_float(float min, float max) {
  float num;
  char term;
  char input_buff[7];
  while (1) {
    printf("Enter an integer between %.2f - %.2f\n", min, max);
    fgets(input_buff, 6, stdin);

    if(sscanf(input_buff,"%f%c", &num, &term) == 2  && is_valid_float_input(num, term, min, max))
      return num;
    else
      printf("Invalid input, enter an int followed by enter/return key\n");
  }
}

bool is_valid_float_input(float num, char term, float min, float max) {
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

int resize_course_assessments(Course *curr_course) {
  if (curr_course->assessment_count <= curr_course->assessment_capacity)
    return 1;

  int new_cap = (int)(curr_course->assessment_capacity * 1.5)+1;

  Assessment **new_list = realloc(curr_course->assessment_list, sizeof(*(new_list))*new_cap);
  if (new_list == NULL) {
    fprintf(stderr, "Unable to resize assessment list, exit and save now\n");
    return 0;
  }
  curr_course->assessment_list = new_list;
  curr_course->assessment_capacity = new_cap;
  return 1;
}

int resize_assessment_entries(Assessment *curr_assessment) {
  if (curr_assessment->curr_entries < curr_assessment->total_entries)
    return 1;

  int new_cap = (int)(curr_assessment->total_entries * 1.5)+1;

  GradeEntry **new_entries = realloc(curr_assessment->entries, sizeof(*(new_entries))*new_cap);
  if (new_entries == NULL) {
    fprintf(stderr, "Unable to resize grade entries, exit and save now\n");
    return 0;
  }
  curr_assessment->entries = new_entries;
  curr_assessment->total_entries = new_cap;
  return 1;
}

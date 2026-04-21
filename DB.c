/* Functions for database*/

#include "DB.h"
#include "db_helper.h"

Database *DB = NULL;


void import_grades(char *filename) {
  return;
}

int add_course(char *course_name) {
  Course *new_course = malloc(sizeof(Course));
  if (new_course == NULL) {
    fprintf(stderr,"Error allocating memory in add_course, please save and exit\n");
    return 0;
  }
  course_name = malloc(sizeof(char) * strlen(course_name) + 1);
  if (course_name == NULL) {
    fprintf(stderr,"Error allocating memory in add_course, please save and exit\n");
    return 0;
  }

  strcpy(new_course->course_name, course_name);

  new_course->assessment_list = calloc(INIT_SIZE, sizeof(Assessment));
   if (new_course->assessment_list == NULL) {
    fprintf(stderr,"Error allocating memory in add_course, please save and exit\n");
    return 0;
  }
  new_course->assessment_capacity = INIT_SIZE;
  new_course->assessment_count = 0;

  fprintf(stdout, "Successfully added %s\n", course_name);
  return 1;
}


void save_grades(char *filename) {
  return;
}

void list_courses(void) {
  return;
}

void edit_course(char *course_name) {
  return;
}

void remove_course(char *course_name) {
  return ;
}

void add_grade(char *course_name, char *assessment_desc, float grade) {
  return;
}

float grade_needed_on_final(char *course_name) {
  return 1;
}

void enter_grade_scale(char *course_name) {
  int num;
  Course *curr_course = get_course(course_name);

  printf("What is the minimum grade for An A+?:\n");
  num = get_valid_integer(0, 100);
  curr_course->grade_scale.a_plus = num;

  printf("What is the minimum grade for An A?:\n");
  num = get_valid_integer(0, num -1);
  curr_course->grade_scale.a = num;

  printf("What is the minimum grade for An A-?:\n");
  num = get_valid_integer(0, num -1);
  curr_course->grade_scale.a_min = num;

  printf("What is the minimum grade for An B+?:\n");
  num = get_valid_integer(0, num -1);
  curr_course->grade_scale.b_plus = num;

  printf("What is the minimum grade for An B?:\n");
  num = get_valid_integer(0, num -1);
  curr_course->grade_scale.b = num;

  printf("What is the minimum grade for An B-?:\n");
  num = get_valid_integer(0, num -1);
  curr_course->grade_scale.b_min = num;

  printf("What is the minimum grade for An C+?:\n");
  num = get_valid_integer(0, num -1);
  curr_course->grade_scale.c_plus = num;

  printf("What is the minimum grade for An C?:\n");
  num = get_valid_integer(0, num -1);
  curr_course->grade_scale.c = num;

  printf("What is the minimum grade for An C-?:\n");
  num = get_valid_integer(0, num -1);
  curr_course->grade_scale.c_min = num;

  printf("What is the minimum grade for An D+?:\n");
  num = get_valid_integer(0, num -1);
  curr_course->grade_scale.d_plus = num;

  printf("What is the minimum grade for An D?:\n");
  num = get_valid_integer(0, num -1);
  curr_course->grade_scale.d = num;

  printf("What is the minimum grade for An D-?:\n");
  num = get_valid_integer(0, num -1);
  curr_course->grade_scale.d_min = num;
}

Course *get_course(char *course_name) {
  for (int i = 0; i < DB->courseCount; i++) {
    if (strcmp_case_insensitive(course_name, DB->courses[i]->course_name))
      return DB->courses[i];
  }
  fprintf(stderr, "Course: %s does not exist in the database\n", course_name);
  return NULL;
}

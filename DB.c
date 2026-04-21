/* Functions for database*/

#include "DB.h"
#include "db_helper.h"

Database *DB = NULL;


void import_grades(char *filename) {
  return;
}

int add_course(char *course_name) {
  if (DB->courseCount >= DB->courseCap) {
    if (!(db_resize()))
      return 0;
  }

  Course *new_course = malloc(sizeof(Course));
  if (new_course == NULL) {
    fprintf(stderr,"Error allocating memory in add_course, please save and exit\n");
    return 0;
  }
  new_course->course_name = malloc(sizeof(char) * strlen(course_name) + 1);
  if (new_course->course_name == NULL) {
    fprintf(stderr,"Error allocating memory in add_course, please save and exit\n");
    free(new_course);
    return 0;
  }

  strcpy(new_course->course_name, course_name);

  new_course->assessment_list = calloc(INIT_SIZE, sizeof(Assessment));
   if (new_course->assessment_list == NULL) {
    fprintf(stderr,"Error allocating memory in add_course, please save and exit\n");
    free(new_course->course_name);
    free(new_course);

    return 0;
  }
  new_course->assessment_capacity = INIT_SIZE;
  new_course->assessment_count = 0;
  enter_grade_scale(new_course);

  DB->courses[DB->courseCount] = new_course;
  DB->courseCount++;
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

void enter_grade_scale(Course *curr_course) {
  int num;

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

void init_DB(int courseCount, int courseCap) {
  if (courseCap < 1 || courseCount < 1) {
    fprintf(stderr, "courseCap: %d and courseCount: %d need to be greatert than 0\n",
      courseCap, courseCount);
    exit(EXIT_FAILURE);
  }

  DB  = malloc(sizeof(Database));
  if (DB == NULL) {
    fprintf(stderr, "Unable to allocate memory in init_DB, exiting\n");
    exit(EXIT_FAILURE);
  }

  DB->courses = calloc(courseCap, sizeof(Course));
  if (DB->courses == NULL) {
    fprintf(stderr, "Unable to allocate memory in init_DB, exiting\n");
    exit(EXIT_FAILURE);
  }

  DB->courseCap = courseCap;
  DB->courseCount = courseCount;
}

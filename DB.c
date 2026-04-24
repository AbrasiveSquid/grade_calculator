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
  new_course->current_grade = 0.0f;

  DB->courses[DB->courseCount] = new_course;
  DB->courseCount++;
  fprintf(stdout, "Successfully added %s\n", course_name);
  return 1;
}


void save_grades(char *filename) {
  return;
}

void list_courses(void) {
  Course *curr_course;
  int num;

  printf("Current Courses:\n\n");
  for (int i = 0; i < DB->courseCount; i++) {
    curr_course = DB->courses[i];
    if (curr_course == NULL)
      continue;
    printf("%d. %s\n", i+1, curr_course->course_name);
  }

  while (1) {
  printf("\nEnter the course number or enter '%d' to exit\n", DB->courseCount+1);
  num = get_valid_integer(1, DB->courseCount+1);

  if (num == DB->courseCount+1)
    break;
  course_details(num-1);
  } 

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
  int num = 101;
  GradeThreshold new_grade;
  char *labels[] = {"A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D+", "D"};
  int count = 0;
  
  for(int i = 0; i < sizeof(labels)/sizeof(labels[0]); i++)
  {
    printf("What is the minimum grade for a %s?:\n", labels[i]);
    num = get_valid_integer(0, num -1);

    strcpy(new_grade.letter_grade, labels[i]);
    curr_course->grade_scale[count++] = new_grade;
  }
}

Course *get_course(char *course_name) {
  for (int i = 0; i < DB->courseCount; i++) {
    if (strcmp_case_insensitive(course_name, DB->courses[i]->course_name))
      return DB->courses[i];
  }
  fprintf(stderr, "Course: %s does not exist in the database\n", course_name);
  return NULL;
}

void init_DB(int courseCap) {
  if (courseCap < 1) {
    fprintf(stderr, "courseCap: %d must be greater than 0\n", courseCap);
    exit(EXIT_FAILURE);
  }

  DB  = malloc(sizeof(Database));
  if (DB == NULL) {
    fprintf(stderr, "Unable to allocate memory in init_DB, exiting\n");
    exit(EXIT_FAILURE);
  }

  DB->courses = malloc(courseCap * sizeof(Course*)); // array of pointers
  if (DB->courses == NULL) { 
    fprintf(stderr, "Unable to allocate memory in init_DB, exiting\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < courseCap; i++) // set the courses array to null
    DB->courses[i] = NULL;

  DB->courseCap = courseCap;
  DB->courseCount = 0;
}


void freeDb(void) {
  if (DB== NULL)
    return;

  int i = 0;
  Course *curr_course;
  for(i = 0; i < DB->courseCap; i++ ) {
    curr_course = DB->courses[i];
    if (curr_course != NULL){
      free(curr_course->assessment_list);
      free(curr_course);
    }
  }
  free(DB->courses);
  free(DB);
}


void course_details(int index) {
  Course *curr_course = DB->courses[index];
  Assessment *curr_assess;
  int i, j;

  printf("Course: %s\n\n",curr_course->course_name);
  printf("Current Grade: %.2f, %s\n", curr_course->current_grade, letter_grade(curr_course, curr_course->current_grade));

  printf("Assessments:\n\n");
  for (i = 0; i < curr_course->assessment_count; i++) {
    curr_assess = curr_course->assessment_list[i];
    
    if (curr_assess->curr_entries > 1){
      for (j = 0; j < curr_assess->curr_entries; j++) {
        printf("%s #%d: ", curr_assess->description, j+1);
        printf("Grade: %2.f, %s",curr_assess->current_grade, letter_grade(curr_course, curr_assess->current_grade));
      }
    }

    else if (curr_assess->curr_entries == 1) {
      printf("%s:\n", curr_assess->description);
      printf("Grade: %2.f, %s",curr_assess->current_grade, letter_grade(curr_course, curr_assess->current_grade));
    }
  }
}

char *letter_grade(Course *curr_course, float grade) {
  for (int i = 0; i < sizeof(curr_course->grade_scale)/sizeof(curr_course->grade_scale[0]); i++) {
    if (grade >= curr_course->grade_scale[i].threshold)
      return curr_course->grade_scale->letter_grade;
  }
  return "F";
}

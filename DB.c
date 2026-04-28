/* Functions for database*/

#include "DB.h"
#include "db_helper.h"
#include <string.h>

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
  FILE *fp;
  int i,j,k,h;
  Course *curr_course;
  Assessment *curr_assess;
  GradeEntry *curr_entry;

  fp = fopen(filename, "w");
  if (fp == NULL) {
    fprintf(stderr, "\nCannot open file: %s, file was not saved\n", filename);
    return;
  }

  // write each course as csv file

  for (i = 0; i < DB->courseCount; i++) {
    curr_course = DB->courses[i];
    fprintf(fp, "course,%s",curr_course->course_name);
    // write the grade scalesa
    for (h = 0; h < 11; h++) {
      fprintf(fp,",%d", curr_course->grade_scale[h].threshold);
    } 
    fprintf(fp,"\n");

    // write out each assessment
    
    for (j = 0; j< curr_course->assessment_count; j++) {
      curr_assess = curr_course->assessment_list[j];
      fprintf(fp, "assessment,%s,%d,%.2f,%d,%d\n", curr_assess->description,curr_assess->equal_weighting, curr_assess->weight,curr_assess->total_entries, curr_assess->curr_entries);
  
      // write out each grade entry

      for (k=0; k < curr_assess->curr_entries; k++) {
        curr_entry = curr_assess->entries[k];
        fprintf(fp, "entry,%.2f,%.2f\n",curr_entry->grade, curr_entry->weight);
      }
    }
  }
}

void list_courses(void) {
  Course *curr_course;

  printf("Current Courses:\n\n");
  if (DB->courseCount == 0) {
    printf("No courses exist in the database\n");
    return;
  }

  for (int i = 0; i < DB->courseCount; i++) {
    curr_course = DB->courses[i];
    if (curr_course == NULL)
      continue;
    printf("%d. %s\n", i+1, curr_course->course_name);
  }
}


void edit_course(char *course_name) {
  return;
}

void remove_course(char *course_name) {
  return ;
}

GradeEntry *create_grade_entry(float grade, float weight) {
  GradeEntry *new_grade = malloc(sizeof(GradeEntry));
  if (new_grade == NULL) {
    fprintf(stderr, "Error allocating memory for new grade entry");
    return NULL;
  }

  new_grade->grade = grade;
  new_grade->weight = weight;
  return new_grade;
}

void get_grade_input(Course *curr_course) {
  Assessment *curr_assess;
  int num, strlen, total_entries, equal_weights;
  float grade, weight=0.0f;
  char input_buf[100];
 

  while(1){
    printf("\nEnter assessment number to add, or enter '0' to add a new assessment. Enter '%d' to exit\n", curr_course->assessment_count +1);
    assessment_list(curr_course);
    num = get_valid_integer(0, curr_course->assessment_count+1);
    if (num == curr_course->assessment_count+1)
      break;
    else if (num == 0) {
      printf("Enter the name of the assessment:\n> ");
      // gets name of assessment, allocates mem on heap for it, then copies to variable
      if (fgets(input_buf, 99, stdin)) {
        strlen = strcspn(input_buf, "\n");
        input_buf[strlen] = '\0';
      }
      printf("How many %s will you have for this type: ", input_buf);
      total_entries = get_valid_integer(1, 100);

      printf("Do all %s have the same grade weighting?\n'1' for yes or '0' for no\n", input_buf);
      equal_weights = get_valid_integer(0, 1);

      if (equal_weights) {
        printf("What is the total grade weight of all the %s? ", input_buf);
        weight = get_valid_float(0.0f, 100.0f);
      }

      // adds assessment to course and resizes if necessary
      Assessment *new_assess = create_assessment(input_buf, equal_weights, weight, total_entries);
      if (curr_course->assessment_count >= curr_course->assessment_capacity) {
        if (!(resize_course_assessments(curr_course))) {
          fprintf(stderr,"Unable to allocate memory to resize, save and exit now\n");
          return;
        }
      }
      curr_course->assessment_list[curr_course->assessment_count] = new_assess;
      curr_course->assessment_count++;

      num = curr_course->assessment_count; // set so can get right index to add grade entry
    }

    // get grade entry details
    curr_assess = curr_course->assessment_list[num-1]; // subtract 1 because stdout was 1 indexed
    printf("What grade did you get for this %s: ", curr_assess->description);
    grade = get_valid_float(0.0f, 100.00f);
    if(!(curr_assess->equal_weighting)) {
      printf("What is the weighting of this %s? ", curr_assess->description);
      weight = get_valid_float(0.0f, 100.00f);
    }
    else
      weight = 0.0f;
    GradeEntry *new_grade = create_grade_entry(grade, weight);
    if (new_grade == NULL) {
      fprintf(stderr, "Error allocating memory, exit and save now\n");
      return;
    }
    
    if (curr_assess->curr_entries >= curr_assess->total_entries) {
      // need to resize
       if (!(resize_assessment_entries(curr_assess))) {
          fprintf(stderr,"Unable to allocate memory to resize, save and exit now\n");
          return;
        }
    }
    curr_assess->entries[curr_assess->curr_entries] = new_grade;
    curr_assess->curr_entries++;
    calculate_assessment_grade(curr_assess);
    calculate_course_grade(curr_course);
  }
}

void calculate_assessment_grade(Assessment *curr_assess) {
  float grade = 0.0f;
  float total_weight = 0.0f;
  if (curr_assess->curr_entries == 0) {
    curr_assess->current_grade = 0.0f;
    return;
  }
  if (curr_assess->equal_weighting) {
  for (int i = 0; i < curr_assess->curr_entries; i++) {
    grade += curr_assess->entries[i]->grade; 
  }
  grade /= curr_assess->curr_entries;
  curr_assess->current_grade = grade;

}
  // if each grade has own weight 
  else {
    for (int i = 0; i < curr_assess->curr_entries; i++) {
      grade += curr_assess->entries[i]->grade * curr_assess->entries[i]->weight;
      total_weight += curr_assess->entries[i]->weight; 
    }
    curr_assess->weight = total_weight;
    curr_assess->current_grade = grade / total_weight;
  }
} 

void calculate_course_grade(Course *curr_course) {
  float grade = 0.0f;
  float current_weight = 0.0f;

  if (curr_course->assessment_count == 0) {
    curr_course->current_grade = 0.0f;
    return;
  }

  for (int i = 0; i <curr_course->assessment_count; i++) {
    grade += (curr_course->assessment_list[i]->current_grade) * (curr_course->assessment_list[i]->weight/100.0f);
    current_weight += curr_course->assessment_list[i]->weight;
  }

  curr_course->current_grade = (grade/current_weight) * 100;
}


float grade_needed_on_final(char *course_name) {
  return 1;
}

Assessment *create_assessment(char *assess_name, int equal_weights, float weights, int total_entries) {
  Assessment *new_assess = malloc(sizeof(Assessment));

  if (new_assess == NULL) {
    fprintf(stderr, "Error allocating memory for a new assessment\n");
    exit(EXIT_FAILURE);
  }

  new_assess->total_entries = total_entries;
  new_assess->curr_entries = 0;
  
  new_assess->description = allocate_string(strlen(assess_name));
  strcpy(new_assess->description, assess_name);

  if (equal_weights)
    new_assess->equal_weighting = 1;
  else
    new_assess->equal_weighting = 0;

  new_assess->weight = weights;

  new_assess->entries = calloc(total_entries, sizeof(*(new_assess->entries)));
  if (new_assess->entries == NULL) {
    fprintf(stderr, "Error allocating memory for a new assessment\n");
    exit(EXIT_FAILURE);
  }

  new_assess->current_grade = 0.0f;

  return new_assess;
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
    new_grade.threshold = num;
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
      printf("\t%s: Assessment Grade: %.2f, %s\n", curr_assess->description, curr_assess->current_grade,letter_grade(curr_course, curr_assess->current_grade));

      for (j = 0; j < curr_assess->curr_entries; j++) {
        printf("\t\t%s #%d: ", curr_assess->description, j+1);
        printf("Grade: %.2f, %s\n",curr_assess->entries[j]->grade, letter_grade(curr_course, curr_assess->entries[j]->grade));
      }
    }

    else if (curr_assess->curr_entries == 1) {
      printf("%s:\n", curr_assess->description);
      printf("Grade: %2.f, %s",curr_assess->current_grade, letter_grade(curr_course, curr_assess->current_grade));
    }
  }
}

void assessment_list(Course * curr_course) {
  Assessment *curr_assess;
  printf("\nAssessments:\n");
  if (curr_course->assessment_count == 0) {
    printf("\tNo Assessments for this course\n");
    return;
  }

  for(int i = 0; i < curr_course->assessment_count; i++) {
    curr_assess = curr_course->assessment_list[i];
    printf("%d. %s\n\tNumber of entries: %d\n", i+1, curr_assess->description, curr_assess->curr_entries);
  }
}

char *letter_grade(Course *curr_course, float grade) {
  for (int i = 0; i < sizeof(curr_course->grade_scale)/sizeof(curr_course->grade_scale[0]); i++) {
    if (grade >= (float)curr_course->grade_scale[i].threshold)
      return curr_course->grade_scale[i].letter_grade;
  }
  return "F";
}


/* Header for the grade calculator database
Holds the Database, and functions to interact with the database
*/

#ifndef DB_H
#define DB_H
#include <stdio.h>
#include <string.h>

#define INIT_SIZE 10

typedef struct {
  float grade; // grade for the entry
  float weight; // weight towards the total course grade for entry

}GradeEntry;

typedef struct {
  int equal_weighting; // flag that is set so all entries are same weight
  int total_entries;
  int curr_entries;
  GradeEntry *entries; // array of structs of grade and weightings
  char *description;
  float current_grade; // current grade for assessment
}Assessment;

  typedef struct {
    int threshold;
    char letter_grade[3];

  }GradeThreshold;

typedef struct {
  // name
  char *course_name;
  Assessment **assessment_list;
  int assessment_count;
  int assessment_capacity;


  float current_grade;

  GradeThreshold grade_scale[11]; // array of structs of the grade thresholds

}Course;

typedef struct {

  Course **courses;
  int courseCount;
  int courseCap;

}Database;

extern Database *DB;

/* initializes the database */
void init_DB(int courseCap);

/* Import grades from a textfile into the database*/
void import_grades(char *filename);

/* Adds a course to the database */
int add_course(char *course_name);

/* Exports the database into a textfile to save*/
void save_grades(char *filename);

/* Lists out all the courses that are in the database*/
void list_courses(void);

/* Edits a course from the database*/
void edit_course(char *course_name);

/*Removes a course permanently from the database*/
void remove_course(char *course_name);

/* adds a grade to an existing course in the database*/
void add_grade(int course_index, int assess_index, float grade);


/* Calculates the percentage needed to get a mark on the final*/
float grade_needed_on_final(char *course_name);

/* adds the cut off for each letter grade into the course object*/
void enter_grade_scale(Course *curr_course);

/* returns the course from the database

Returns:
  NULL if course doesn't exist
*/
Course *get_course(char *course_name);

// Frees all the allocated memory for the database
void freeDb(void);

/* prints out the details of the course */
void course_details(int index);

// Returns the current letter grade for the course
char *letter_grade(Course *curr_course, float grade);

// Prints out the list of a course's assessments
void assessment_list(Course * curr_course);

// gets input from user on what assessment to add a grade
void get_grade_input(int course_index);

// creates and returns a pointer to a new assessment
Assessment *create_assessment(char *assess_name, int equal_weights, int total_entries);



#endif

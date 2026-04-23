/* Header for the grade calculator database
Holds the Database, and functions to interact with the database
*/

#ifndef DB_H
#define DB_H
#include <stdio.h>
#include <string.h>

#define INIT_SIZE 10

typedef struct {
  float grade;
  int total_entries;
  int curr_entries;
  char *description;

}Assessment;

typedef struct {
  // name
  char *course_name;
  Assessment *assessment_list;
  int assessment_count;
  int assessment_capacity;


  float current_grade;
  // grade breakdown
  struct {
    int a_plus;
    int a;
    int a_min;
    int b_plus;
    int b;
    int b_min;
    int c_plus;
    int c;
    int c_min;
    int d_plus;
    int d;
    int d_min;
  }grade_scale;
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
void add_grade(char *course_name, char *assessment_desc, float grade);

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


#endif

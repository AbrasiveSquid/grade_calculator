/* Header for the grade calculator database
Holds the Database, and functions to interact with the database
*/

#ifndef DB_H
#define DB_H

#define INIT_SIZE 10

typedef struct {
  float grade;
  char *description;
}Assessment; 

typedef struct {
  // name
  // grade breakdown
  // assignments
  // 

  char *course_name;

}Course;

typedef struct {

  Course **courses;
  int courseCount;
  int courseCap;

}Database;



extern Database *DB;



/* Import grades from a textfile into the database*/
void import_grades(char *filename);

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


#endif
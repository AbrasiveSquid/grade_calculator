/* Main loop of the program */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "DB.h"
#include "db_helper.h"

// void program_loop(char *filename);



/* Gets user input before calling input_grades()*/
void import_grades_input(void);

/* Gets user input before calling input_grades()*/
void save_grades_input(void);

/* Gets user input before calling input_grades()*/
void list_courses_input(void);

/* Gets user input before calling input_grades()*/
void edit_courses_input(void);

/* Gets user input before calling input_grades()*/
void remove_courses_input(void);

/* gets input from user and returns an array of characters of that input*/
void get_user_input(char input_buffer[], int size);

/* gets input from user to add a new course*/
void add_course_input(void);



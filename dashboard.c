#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dashboard.h"
#include "DB.h"

int main(void) {
  int option;
  int ch;

  
  while (1) {
    printf("\nSelect an option:\n1. Import Grades\n2. Save Grades\n3. List Courses\n4. Edit Course\n5. Remove Course\n6. Exit\n>  ");

    if (scanf("%d", &option) != 1 || option < 1 || option > 6) {
      fprintf(stderr, "Incorrect option selected: ");

      option = -1;
    }
    while ((ch = getchar()) != '\n' && ch != EOF); // clears input buffer

    switch (option) {
      case 1:
        import_grades_input();
        break;
      case 2:
        save_grades_input();
        break;
      case 3:
        list_courses_input();
        break;
      case 4:
        edit_courses_input();
        break;
      case 5:
        remove_courses_input();
        break;
      case 6:
        return 0;
      default:
        fprintf(stderr, "Incorrect option selected\n");
        continue;
    }
    
  }
  return 0;
}


void import_grades_input(void) {
  FILE *fp;
  char filename[100];
  printf("\nEnter a filename that was previously used to save grades: ");
  get_user_input(filename, 100);

  while ((fp = fopen(filename, "r")) == NULL) {
    printf("'%s' is an incorrect filename, try entering the filename again or 'q' to quit\n> ", filename);
    get_user_input(filename, 100);
    if (strcmp(filename, "q") == 0) 
      exit(EXIT_SUCCESS);


  }
  fclose(fp);
  import_grades(filename);
}

void get_user_input(char input_buffer[], int size) {
  int ch, i = 0;

  while ((ch = getchar()) != '\n' && ch != EOF && i < size-1 )
    input_buffer[i++] = ch;

  input_buffer[i] = '\0';
}


void save_grades_input(void) {
  return;
}


void list_courses_input(void) {
  return;
}


void edit_courses_input(void) {
  return;
}

void remove_courses_input(void) {
  return;
}
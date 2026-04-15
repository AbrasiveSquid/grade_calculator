#include <stdio.h>
// #include <stdlib.h>
#include "dashboard.h"
#include "DB.h"

int main(void) {
  int option;

  
  while (1) {
    printf("Select an option:\n1. Import Grades\n2. Save Grades\n3. List Courses\n4. Edit Course\n5. Remove Course\n6. Exit\n>  ");

    if (scanf("%d", &option) != 1) {
      fprintf(stderr, "Incorrect option selected: ");
      continue;
    }
    if (option < 1 || option > 6){
      fprintf(stderr, "Incorrect option selected: ");
      continue;
    }

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
        fprintf(stderr, "Incorrect option selected:");
        continue;
    }
    
  }
  return 0;
}


void import_grades_input(void) {
  return;
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
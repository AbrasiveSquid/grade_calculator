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

}Course;

typedef struct {

  Course **courses;
  int courseCount;
  int courseCap;

}Database;



extern Database *DB;


#endif
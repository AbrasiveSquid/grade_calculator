#include "../db_helper.h"
#include <assert.h>
#include <stdio.h>

void test_is_valid_input(void) {
  // Test: valid input inside range
  assert(is_valid_input(5, '\n', 1, 10) == 1);

  // test: input below minimum
  assert(is_valid_input(0, '\n', 1, 10) == 0);

  // test: input above max
  assert(is_valid_input(11, '\n', 1, 10) == 0);
  // test did not enter newline
  assert(is_valid_input(5,' ', 1, 10) == 0);

  printf("all test_is_valid_input tests passed.\n");
}

void test_strcmp_case_insensitive(void) {
  // Test: indentical strings
  assert(strcmp_case_insensitive("hello", "hello") == 1);

  // test mixed case
  assert(strcmp_case_insensitive("hello", "HellO") == 1);

  // test all uppercase
  assert(strcmp_case_insensitive("hello", "HELLO") == 1);

  // test same length
  assert(strcmp_case_insensitive("hello", "apple") == 0);


  // test same first word but different second
  assert(strcmp_case_insensitive("hello", "HELLO world") == 0);
  assert(strcmp_case_insensitive("HELLO world", "hello") == 0);


  // test 5 spaces
  assert(strcmp_case_insensitive("     ", "     ") == 1);

  // test punctuation and non-alpha mixed char
  assert(strcmp_case_insensitive("hello!?", "hello!?") == 1);
  assert(strcmp_case_insensitive("CompSci 101!", "compsci 101!") == 1);
  assert(strcmp_case_insensitive("12345", "12345") == 1);

  // test empty string
  assert(strcmp_case_insensitive("", "") == 1);
  assert(strcmp_case_insensitive("", "hello") == 0);
  assert(strcmp_case_insensitive("hello", "") == 0);

  printf("all test_strcmp_case_insensitive tests passed.\n");
}




int main(void) {

  test_is_valid_input();
  test_strcmp_case_insensitive();
  return 0;
}

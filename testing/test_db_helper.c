#include "../db_helper.h"
#include <assert.h>
#include <stdio.h>

void test_is_valid_input(void) {
  // testing is_valid_input
  // Test: valid input inside range
  assert(is_valid_input(5, '\n', 1, 10) == 1);

  // test: input below minimum
  assert(is_valid_input(0, '\n', 1, 10) == 0);

  // test: input above max
  assert(is_valid_input(11, '\n', 1, 10) == 0);
  // test did not enter newline
  assert(is_valid_input(5,' ', 1, 10) == 0);

  printf("all validation tests passed.\n");
}
int main(void) {

  test_is_valid_input();
  return 0;
}

#include "solve.h"
#include "tests.h"

bool test_row_full() {
  return false;
}

bool test_col_full() {
  return false;
}

bool test_group_full() {
  return false;
}

bool test_solved() {
  return false;
}

int main() {
  test(test_row_full, "row_full");
  test(test_col_full, "col_full");
  test(test_group_full, "group_full");
  test(test_solved, "solved");
}

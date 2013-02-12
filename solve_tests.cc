#include "puzzle.h"
#include "solve.h"
#include "tests.h"

#include <iostream>
#include <stdexcept>

Row make_row(std::string row_str) {
  Row row;
  for (std::string::const_iterator ch = row_str.begin();
       ch != row_str.end();
       ch++) {
    Square sq;
    sq.row = 0;
    sq.col = 0;
    sq.val = *ch - '0';
    row.push_back(sq);
  }
  return row;
}

void test_row_full() {
  deftest("row_full");
  assert(row_full(make_row("123456789")), "full row");
  assert(!row_full(make_row("123436789")), "duplicate value");
  assert(!row_full(make_row("123406789")), "missing value");
}

bool test_col_full() {
  return true;
}

bool test_group_full() {
  return true;
}

bool test_solved() {
  return true;
}

int main() {
  try {
    test_row_full();
  } catch (std::logic_error err) {
    std::cout << "Test failed: " << err.what() << std::endl;
  }
}

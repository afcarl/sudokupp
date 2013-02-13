#include "puzzle.h"
#include "solve.h"
#include "tests.h"

#include <iostream>
#include <stdexcept>

void print(std::vector<int> ints) {
  for (std::vector<int>::const_iterator i = ints.begin(); i != ints.end(); i++)
    std::cout << *i;
  std::cout << std::endl;
}

Row make_row(std::string row_str) {
  Row row;
  for (std::string::const_iterator ch = row_str.begin();
       ch != row_str.end();
       ch++) {
    Square sq;
    sq.row = 0;
    sq.col = 0;
    sq.val = *ch - '0';
    fill(sq.possible_vals, 1, 10);
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

Puzzle make_col(std::string col_str, int col) {
  Puzzle puzzle = make_puzzle();
  Row row = make_row(col_str);
  for (int i = 0; i < ROWS; i++)
    puzzle[i][col].val = row[i].val;
  return puzzle;
}

void test_col_full() {
  deftest("col_full");
  assert(col_full(make_col("321987456", 2), 2), "full column");
  assert(!col_full(make_col("321987436", 2), 2), "duplicate value");
  assert(!col_full(make_col("321987406", 2), 2), "missing value");
}

Puzzle make_group(std::string group_str, int x, int y) {
  Puzzle puzzle = make_puzzle();
  Row row = make_row(group_str);
  for (int i = 0; i < ROWS/3; i++)
    for (int j = 0; j < COLS/3; j++)
      puzzle[x+i][y+j].val = row[3*i + j].val;
  return puzzle;
}

void test_group_full() {
  deftest("group_full");
  assert(group_full(make_group("321987456", 2, 3), 2, 3), "full group");
  assert(!group_full(make_group("321987436", 2, 3), 2, 3), "duplicate value");
  assert(!group_full(make_group("321987406", 2, 3), 2, 3), "missing value");
}

Puzzle make_puzzle(std::string puzzle_str) {
  Puzzle puzzle = make_puzzle();
  for (int i = 0; i < puzzle_str.size(); i++)
    puzzle[i / ROWS][i % COLS].val = puzzle_str[i] - '0';
  return puzzle;
}

void test_solved() {
  deftest("solved");
  assert(solved(make_puzzle("123456789"
                            "456789123"
                            "789123456"
                            "234567891"
                            "567891234"
                            "891234567"
                            "345678912"
                            "678912345"
                            "912345678")), "solved puzzle");
  assert(!solved(make_puzzle("123456789"
                             "456789123"
                             "789123456"
                             "234567891"
                             "567891234"
                             "891234567"
                             "345678912"
                             "678917345" // note the extra 7
                             "912345678")), "duplicate value");
  assert(!solved(make_puzzle("123456789"
                             "456789123"
                             "789123456"
                             "234567891"
                             "567891234"
                             "891234567"
                             "345678912"
                             "678912045" // note the 0
                             "912345678")), "missing value");
}

void test_eliminate_row() {
  deftest("eliminate_row");
  Puzzle puzzle = make_puzzle();

  puzzle[3] = make_row("123056709");
  assert(puzzle[3][7].val == 0, "unknown value");
  assert(eliminate_row(puzzle, 3, 7), "change didn't occur");
  assert(puzzle[3][7].val == 0, "still unknown");
  assert(puzzle[3][7].possible_vals.size() == 2, "elimination");
  assert(puzzle[3][7].possible_vals[0] == 4, "elimination");
  assert(puzzle[3][7].possible_vals[1] == 8, "elimination");
  assert(!eliminate_row(puzzle, 3, 7), "do it again---no change");

  puzzle[2] = make_row("123405678");
  assert(puzzle[2][4].val == 0, "unknown value");
  assert(eliminate_row(puzzle, 2, 4), "change occurred");
  assert(puzzle[2][4].val == 9, "update value");
  assert(puzzle[2][4].possible_vals.empty(), "no possibilities remain");
  assert(!eliminate_row(puzzle, 2, 4), "again, no change occurred");
}

void test_eliminate_column() {
  deftest("eliminate_column");
  Puzzle puzzle = make_col("123056709", 4);
  assert(puzzle[3][4].val == 0, "unknown value");
  assert(eliminate_column(puzzle, 3, 4), "change didn't occur");
  assert(puzzle[3][4].val == 0, "still unknown");
  assert(puzzle[3][4].possible_vals.size() == 2, "elimination");
  assert(puzzle[3][4].possible_vals[0] == 4, "elimination");
  assert(puzzle[3][4].possible_vals[1] == 8, "elimination");
  assert(!eliminate_column(puzzle, 3, 4), "do it again---no change");

  puzzle = make_col("123405678", 4);
  assert(puzzle[4][4].val == 0, "unknown value");
  assert(eliminate_column(puzzle, 4, 4), "change occurred");
  assert(puzzle[4][4].val == 9, "update value");
  assert(puzzle[4][4].possible_vals.empty(), "no possibilities remain");
  assert(!eliminate_column(puzzle, 4, 4), "again---no change occurred");
}

void test_eliminate_group() {
}

void test_eliminate() {
}

int main() {
  try {
    test_row_full();
    test_col_full();
    test_group_full();
    test_solved();
    test_eliminate_row();
    test_eliminate_column();
    test_eliminate_group();
    test_eliminate();
  } catch (std::logic_error err) {
    std::cout << "Test failed: " << err.what() << std::endl;
  }
}

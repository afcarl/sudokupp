#include "puzzle.h"
#include "solve.h"
#include "tests.h"

#include <iostream>
#include <stdexcept>

const std::string kPuzzleString =
  "086000025"
  "000003640"
  "070050000"
  "015300060"
  "400905008"
  "090008570"
  "000070030"
  "039200000"
  "150000490";

void print(std::vector<int> ints) {
  for (std::vector<int>::const_iterator i = ints.begin(); i != ints.end(); i++)
    std::cout << *i;
  std::cout << std::endl;
}

Row make_row(std::string row_str) {
  Row row;
  for (std::string::const_iterator ch = row_str.begin();
       ch != row_str.end(); ch++) {
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
  try {
    row_full(make_row("123436789"));
    assert(false, "duplicate value");
  } catch (std::logic_error) {
  }
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
  try {
    col_full(make_col("321987436", 2), 2);
    assert(false, "duplicate value");
  } catch (std::logic_error) {
  }
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
  try {
    group_full(make_group("321987436", 2, 3), 2, 3);
    assert(false, "duplicate value");
  } catch (std::logic_error) {
  }
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
  try {
    solved(make_puzzle("123456789"
                       "456789123"
                       "789123456"
                       "234567891"
                       "567891234"
                       "891234567"
                       "345678912"
                       "678917345" // note the extra 7
                       "912345678"));
    assert(false, "duplicate value");
  } catch (std::logic_error) {
  }
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
  assert(puzzle[3][7].possible_vals.front() == 4, "elimination");
  assert(puzzle[3][7].possible_vals.back() == 8, "elimination");
  assert(!eliminate_row(puzzle, 3, 7), "do it again---no change");
}

void test_eliminate_column() {
  deftest("eliminate_column");
  Puzzle puzzle = make_col("123056709", 4);
  assert(puzzle[3][4].val == 0, "unknown value");
  assert(eliminate_column(puzzle, 3, 4), "change didn't occur");
  assert(puzzle[3][4].val == 0, "still unknown");
  assert(puzzle[3][4].possible_vals.size() == 2, "elimination");
  assert(puzzle[3][4].possible_vals.front() == 4, "elimination");
  assert(puzzle[3][4].possible_vals.back() == 8, "elimination");
  assert(!eliminate_column(puzzle, 3, 4), "do it again---no change");
}

void test_eliminate_group() {
  deftest("eliminate_group");
  Puzzle puzzle = make_group("123056709", 3, 3);
  assert(puzzle[4][3].val == 0, "unknown value");
  assert(eliminate_group(puzzle, 4, 3), "change didn't occur");
  assert(puzzle[4][3].val == 0, "still unknown");
  assert(puzzle[4][3].possible_vals.size() == 2, "elimination length");
  assert(puzzle[4][3].possible_vals.front() == 4, "elimination val.front()");
  assert(puzzle[4][3].possible_vals.back() == 8, "elimination val.back()");
  assert(!eliminate_group(puzzle, 4, 3), "do it again---no change");
}

void test_eliminate_square() {
  deftest("eliminate square");
  Puzzle puzzle = make_puzzle();
  read_puzzle(puzzle, kPuzzleString);
  // requires row and column elimination
  assert(eliminate(puzzle, 1, 1), "change occurred");
  assert(puzzle[1][1].val == 2, "value of 1,1");
  // requires row, column, and group elimination
  assert(eliminate(puzzle, 1, 2), "change occurred");
  assert(puzzle[1][2].val == 1, "value of 1,2");
}

void test_eliminate_square_no_options() {
  deftest("eliminate_square_no_options");
  Puzzle puzzle = make_puzzle();
  read_puzzle(puzzle, 
              "086000025"
              "200003640"
              "070050000"
              "015300060"
              "400905008"
              "090008570"
              "000070030"
              "039200000"
              "150000490");
  try {
    eliminate(puzzle, 1, 1);
    assert(false, "no possibilities remain");
  } catch (std::logic_error) {
  }
}

void test_eliminate() {
  deftest("eliminate square");
  Puzzle puzzle = make_puzzle();
  read_puzzle(puzzle, kPuzzleString);
  assert(eliminate1(puzzle), "change occurred");
  assert(puzzle[1][1].val == 2, "value of 1,1");
  assert(puzzle[1][2].val == 1, "value of 1,2");
}

void test_guess() {
  deftest("test_guess");
  Puzzle puzzle = make_puzzle();
  read_puzzle(puzzle,
              "802060040"
              "050000803"
              "000005700"
              "008090000"
              "907080504"
              "000010600"
              "001900300"
              "406000050"
              "080070402");
  Square g = guess(puzzle);
  assert(g.row == 0, "guess row");
  assert(g.col == 1, "guess col");
  assert(g.val == 1, "guess val"); 
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
    test_eliminate_square();
    test_eliminate_square_no_options();
    test_eliminate();
    test_guess();
  } catch (std::logic_error err) {
    std::cout << "Test failed (" << testname() << "): "
              << err.what() << std::endl;
  }
}

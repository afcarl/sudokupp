#include "solve.h"

#include <stdexcept>
#include <iostream>
#include <cstdlib>

bool sq_order(const Square& left, const Square& right) {
  return left.val < right.val;
}

bool row_full(Row row) {
  sort(row.begin(), row.end(), sq_order);
  if (row[0].val != 1)
    return false;
  for (int i = 1; i < COLS; i++)
    if (row[i].val != row[i-1].val + 1)
      return false;
  return true;
}

bool col_full(const Puzzle& puzzle, int col) {
  Row row;
  for (int i = 0; i < ROWS; i++)
    row.push_back(puzzle[i][col]);
  return row_full(row);
}

bool group_full(const Puzzle& puzzle, int x, int y) {
  Row row;
  for (int i = x; i < x+3; i++)
    for (int j = y; j < y+3; j++)
      row.push_back(puzzle[i][j]);
  return row_full(row);
}

bool solved(const Puzzle& puzzle) {
  for (int i = 0; i < ROWS; i++)
    if (!row_full(puzzle[i]))
      return false;
  for (int j = 0; j < COLS; j++)
    if (!col_full(puzzle, j))
      return false;
  for (int i = 0; i < ROWS/3; i++)
    for (int j = 0; j < COLS/3; j++)
      if (!group_full(puzzle, 3*i, 3*j))
        return false;
  return true;
}

bool eliminate_row(Puzzle& puzzle, int row, int col) {
  if (puzzle[row][col].val != EMPTY)
    return false;

  bool changed = false;
  for (int j = 0; j < COLS; j++)
    if (j != col && puzzle[row][j].val != EMPTY)
      changed |= eliminate(puzzle, row, col, puzzle[row][j].val);
  return changed;
}

bool eliminate_column(Puzzle& puzzle, int row, int col) {
  if (puzzle[row][col].val != EMPTY)
    return false;

  bool changed = false;
  for (int i = 0; i < ROWS; i++)
    if (i != row && puzzle[i][col].val != EMPTY)
      changed |= eliminate(puzzle, row, col, puzzle[i][col].val);
  return changed;
}

bool eliminate_group(Puzzle& puzzle, int row, int col) {
  if (puzzle[row][col].val != EMPTY)
    return false;
  bool changed = false;
  int base_row = (row / GROUP_ROWS) * GROUP_ROWS;
  int base_col = (col / GROUP_COLS) * GROUP_COLS;
  for (int i = base_row; i < base_row + GROUP_ROWS; i++)
    for (int j = base_col; j < base_col + GROUP_COLS; j++)
      if (i != row || j != col)
        changed |= eliminate(puzzle, row, col, puzzle[i][j].val);
  return changed;
}

bool eliminate(Puzzle& puzzle, int row, int col) {
  bool changed = false;
  changed |= eliminate_row(puzzle, row, col);
  changed |= eliminate_column(puzzle, row, col);
  changed |= eliminate_group(puzzle, row, col);
  return changed;
}

bool eliminate(Puzzle& puzzle) {
  bool changed = false;
  for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLS; j++)
      changed |= eliminate(puzzle, i, j);
  return changed;
}

bool eliminate(Puzzle& puzzle, int row, int col, int val) {
  bool changed = false;
  Square& sq = puzzle[row][col];
  for (std::vector<int>::iterator iter = sq.possible_vals.begin();
       iter != sq.possible_vals.end();
       iter++) {
    if (*iter == val) {
      iter = sq.possible_vals.erase(iter);
      changed = true;
      break;
    }
  }
  if (sq.possible_vals.size() == 1) {
    sq.val = sq.possible_vals.front();
    sq.possible_vals.clear();
    changed = true;
  }
  return changed;
}

void eliminate(Puzzle& puzzle, const Square& guess) {
  eliminate(puzzle, guess.row, guess.col, guess.val);
}

Square guess(const Puzzle& puzzle) {
  return Square();
}

Puzzle apply_guess(const Puzzle& puzzle, const Square& guess) {
  return puzzle;
}

Puzzle solve(Puzzle puzzle) {
  // // While puzzle is not solved:
  // while (!solved(puzzle)) {
  //   // 1. Run elimination until there are no changes.
  //   while (eliminate(puzzle));
  //   if (solved(puzzle))
  //     break;
  //   // 2. Choose a square and make a guess.
  //   Square sq = guess(puzzle);
  //   try {
  //     //    a. Attempt to solve with that guess.
  //     //    b. If solving succeeds, return the puzzle.
  //     return solve(apply_guess(puzzle, sq));
  //   } catch (std::invalid_argument) {
  //     //    c. Otherwise, eliminate that guess.
  //     eliminate(puzzle, sq);
  //   }
  // }
  return puzzle;
}

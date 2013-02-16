#include "solve.h"

#include <stdexcept>
#include <iostream>
#include <cstdlib>

bool sq_order(const Square& left, const Square& right) {
  return left.val < right.val;
}

void fill(bool things[], int size, bool val) {
  for (int i = 0; i < size; i++)
    things[i] = val;
}

bool row_full(const Row& row) {
  bool vals[COLS];
  fill(vals, COLS, false);
  for (Row::const_iterator sq = row.begin(); sq != row.end(); sq++) {
    if (sq->val == 0)
      return false;
    if (vals[sq->val-1])
      throw std::logic_error("duplicate value");
    vals[sq->val-1] = true;
  }
  return true;
}

bool col_full(const Puzzle& puz, int col) {
  bool vals[ROWS];
  fill(vals, ROWS, false);
  for (Puzzle::const_iterator row = puz.begin(); row != puz.end(); row++) {
    const Square& sq = (*row)[col];
    if (sq.val == 0)
      return false;
    if (vals[sq.val-1])
      throw std::logic_error("duplicate value");
    vals[sq.val-1] = true;
  }
  return true;
}

bool group_full(const Puzzle& puzzle, int x, int y) {
  bool vals[ROWS];
  fill(vals, ROWS, false);
  for (int i = x; i < x+3; i++)
    for (int j = y; j < y+3; j++) {
      const Square& sq = puzzle[i][j];
      if (sq.val == 0)
        return false;
      if (vals[sq.val-1])
        throw std::logic_error("duplicate value");
      vals[sq.val-1] = true;
    }
  return true;
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
  if (puzzle[row][col].val != EMPTY)
    return false;

  // Eliminate possible values
  bool changed = false;
  changed |= eliminate_row(puzzle, row, col);
  changed |= eliminate_column(puzzle, row, col);
  changed |= eliminate_group(puzzle, row, col);

  // Check for a solution
  Square& sq = puzzle[row][col];
  if (sq.possible_vals.size() == 1) {
    sq.val = sq.possible_vals.front();
    sq.possible_vals.clear();
    changed = true;
  } else if (sq.possible_vals.size() == 0) {
    throw std::logic_error("no possibilities remain");
  }

  return changed;
}

bool eliminate1(Puzzle& puzzle) {
  bool changed = false;
  for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLS; j++)
      changed |= eliminate(puzzle, i, j);
  return changed;
}

bool eliminate(Puzzle& puzzle) {
  bool changed = false;
  bool ret = false;
  do {
    changed = eliminate1(puzzle);
    ret |= changed;
  } while (changed);
  return ret;
}

bool eliminate(Puzzle& puzzle, int row, int col, int val) {
  bool changed = false;
  Square& sq = puzzle[row][col];
  for (std::list<int>::iterator iter = sq.possible_vals.begin();
       iter != sq.possible_vals.end();
       iter++) {
    if (*iter == val) {
      iter = sq.possible_vals.erase(iter);
      changed = true;
      break;
    }
  }
  return changed;
}

void eliminate(Puzzle& puzzle, const Square& guess) {
  eliminate(puzzle, guess.row, guess.col, guess.val);
}

Square guess(const Puzzle& puz) {
  for (Puzzle::const_iterator row = puz.begin(); row != puz.end(); row++)
    for (Row::const_iterator sq = row->begin(); sq != row->end(); sq++)
      if (sq->val == EMPTY) {
        Square guess;
        guess.row = sq->row;
        guess.col = sq->col;
        guess.val = sq->possible_vals.front();
        return guess;
      }
  throw std::logic_error("no possible guesses");
}

Puzzle apply_guess(const Puzzle& puzzle, const Square& guess) {
  Puzzle guessed = puzzle;
  guessed[guess.row][guess.col] = guess;
  return guessed;
}

Puzzle solve(Puzzle puzzle) {
  while (!solved(puzzle)) {
    eliminate(puzzle);
    if (solved(puzzle))
      break;
    Square sq = guess(puzzle);
    try {
      return solve(apply_guess(puzzle, sq));
    } catch (std::logic_error) {
      eliminate(puzzle, sq);
    }
  }
  return puzzle;
}

#include "puzzle.h"

#include <iostream>
#include <string>

Puzzle make_puzzle() {
  Puzzle puzzle(ROWS);
  for (int i = 0; i < ROWS; i++) {
    puzzle[i] = Row(COLS);
    for (int j = 0; j < COLS; j++) {
      Square sq;
      sq.row = i;
      sq.col = j;
      sq.val = EMPTY;
    }
  }
  return puzzle;
}

std::istream& read_puzzle(Puzzle& puzzle, std::istream& stream) {
  for (int i = 0; i < ROWS; i++) {
    std::string row;
    if (!(stream >> row))
      return stream;
    for (int j = 0; j < COLS; j++) {
      puzzle[i][j] = Square();
      puzzle[i][j].row = i;
      puzzle[i][j].col = j;
      puzzle[i][j].val = row[j] - '0';
    }
  }
  return stream;
}

std::ostream& write_puzzle(const Puzzle& puzzle, std::ostream& stream) {
  for (Puzzle::const_iterator row = puzzle.begin(); row != puzzle.end(); row++) {
    for (Row::const_iterator sq = row->begin(); sq != row->end(); sq++) {
      stream << sq->val;
    }
    stream << std::endl;
  }
  return stream;
}

Puzzle copy_puzzle(const Puzzle& puzzle) {
  Puzzle blank = make_puzzle();
  for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLS; j++)
      blank[i][j] = puzzle[i][j];
  return blank;
}

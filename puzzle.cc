#include "puzzle.h"

#include <iostream>
#include <string>

void fill(std::vector<int>& vec, int start, int end) {
  for (int i = start; i < end; i++)
    vec.push_back(i);
}

Puzzle make_puzzle() {
  Puzzle puzzle(ROWS);
  for (int i = 0; i < ROWS; i++) {
    puzzle[i] = Row(COLS);
    for (int j = 0; j < COLS; j++) {
      puzzle[i][j] = Square();
      puzzle[i][j].row = i;
      puzzle[i][j].col = j;
      puzzle[i][j].val = EMPTY;
      fill(puzzle[i][j].possible_vals, 1, 10);
    }
  }
  return puzzle;
}

std::istream& read_puzzle(Puzzle& puzzle, std::istream& stream) {
  std::string puzzle_str;
  for (int i = 0; i < ROWS; i++) {
    std::string row;
    if (!(stream >> row))
      return stream;
    puzzle_str += row;
  }
  read_puzzle(puzzle, puzzle_str);
  return stream;
}

void read_puzzle(Puzzle& puzzle, const std::string& puzzle_str) {
  for (int i = 0; i < puzzle_str.size(); i++)
    puzzle[i / COLS][i % COLS].val = puzzle_str[i] - '0';
}

std::ostream& write_puzzle(const Puzzle& puzzle, std::ostream& stream) {
  return stream << write_puzzle(puzzle);
}

std::string write_puzzle(const Puzzle& puzzle) {
  std::string puzzle_str;
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++)
      puzzle_str.push_back(puzzle[i][j].val + '0');
    puzzle_str.push_back('\n');
  }
  return puzzle_str;
}

Puzzle copy_puzzle(const Puzzle& puzzle) {
  Puzzle blank = make_puzzle();
  for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLS; j++)
      blank[i][j] = puzzle[i][j];
  return blank;
}

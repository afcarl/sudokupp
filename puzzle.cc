#include "puzzle.h"

#include <iostream>
#include <string>

void fill(std::list<int>& list, int start, int end) {
  for (int i = start; i < end; i++)
    list.push_back(i);
}

Puzzle make_puzzle() {
  Puzzle puzzle;
  for (int i = 0; i < ROWS; i++) {
    puzzle.push_back(Row(COLS));
    for (int j = 0; j < COLS; j++) {
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

char printval(const Square& sq) {
  return sq.val + '0';
}

std::string write_puzzle(const Puzzle& puz) {
  std::string puzzle_str;
  for (PuzzleIter row = puz.begin(); row != puz.end(); row++) {
    transform(row->begin(), row->end(), std::back_inserter(puzzle_str), printval);
    puzzle_str.push_back('\n');
  }
  return puzzle_str;
}


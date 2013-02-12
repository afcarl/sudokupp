#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include <ios>

const int EMPTY = 0;
const int ROWS = 9;
const int COLS = 9;

struct Square {
  int row;
  int col;
  int val;
};

typedef std::vector<Square> Row;
typedef std::vector<Row> Board;

// Create an empty board.
Board make_board();

// Read a board from an input stream.
std::istream& read_board(Board& board, std::istream& stream);

// Write a board to an input stream.
std::ostream& write_board(const Board& board, std::ostream& stream);

#endif

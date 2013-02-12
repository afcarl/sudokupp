#include "board.h"

#include <iostream>
#include <string>

Board make_board() {
  Board board(ROWS);
  for (int i = 0; i < ROWS; i++) {
    board[i] = Row(COLS);
    for (int j = 0; j < COLS; j++) {
      Square sq;
      sq.row = i;
      sq.col = j;
      sq.val = EMPTY;
    }
  }
  return board;
}

std::istream& read_board(Board& board, std::istream& stream) {
  for (int i = 0; i < ROWS; i++) {
    std::string row;
    if (!(stream >> row))
      return stream;
    for (int j = 0; j < COLS; j++) {
      board[i][j] = Square();
      board[i][j].row = i;
      board[i][j].col = j;
      board[i][j].val = row[j] - '0';
    }
  }
  return stream;
}

std::ostream& write_board(const Board& board, std::ostream& stream) {
  for (Board::const_iterator row = board.begin(); row != board.end(); row++) {
    for (Row::const_iterator sq = row->begin(); sq != row->end(); sq++) {
      stream << sq->val;
    }
    stream << std::endl;
  }
  return stream;
}

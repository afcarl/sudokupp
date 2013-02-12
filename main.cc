#include <iostream>

#include "board.h"

int main(int argc, char* argv[]) {
  Board board = make_board();
  if (!read_board(board, std::cin)) {
    std::cout << "Error: failed to read board!";
    return 1;
  }
  write_board(board, std::cout);
  return 0;
}

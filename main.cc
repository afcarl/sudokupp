#include <iostream>

#include "puzzle.h"

int main(int argc, char* argv[]) {
  Puzzle puzzle = make_puzzle();
  if (!read_puzzle(puzzle, std::cin)) {
    std::cout << "Error: failed to read puzzle!";
    return 1;
  }
  write_puzzle(puzzle, std::cout);
  return 0;
}

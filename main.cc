#include <iostream>

#include "puzzle.h"
#include "solve.h"

int main(int argc, char* argv[]) {
  Puzzle puzzle = make_puzzle();
  if (!read_puzzle(puzzle, std::cin)) {
    std::cout << "Error: failed to read puzzle!";
    return 1;
  }

  std::cout << "Puzzle:" << std::endl;
  write_puzzle(puzzle, std::cout);

  Puzzle solution = solve(puzzle);
  std::cout << std::endl << "Solution:" << std::endl;
  write_puzzle(puzzle, std::cout);

  return 0;
}

#include <iostream>

#include "puzzle.h"
#include "solve.h"

int main(int argc, char* argv[]) {
  Puzzle puzzle = make_puzzle();
  if (!read_puzzle(puzzle, std::cin)) {
    std::cout << "Error: failed to read puzzle!";
    return 1;
  }
  Puzzle solution = solve(puzzle);
  write_puzzle(solution, std::cout);
  return 0;
}

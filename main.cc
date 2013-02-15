#include "puzzle.h"
#include "solve.h"

#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[]) {
  Puzzle puzzle = make_puzzle();
  if (!read_puzzle(puzzle, std::cin)) {
    std::cout << "Error: failed to read puzzle!";
    return 1;
  }
  try {
    Puzzle solution = solve(puzzle);
    write_puzzle(solution, std::cout);
  } catch (std::logic_error e) {
    std::cout << "Error: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}

#include "solve.h"

bool solved(const Puzzle& puzzle) {
  return true;
}

bool eliminate(Puzzle& puzzle) {
  return false;
}

Square guess(const Puzzle& puzzle) {
  return Square();
}

Puzzle solve_puzzle(const Puzzle& puzzle) {
  // While puzzle is not solved:
  // 1. Run elimination until there are no changes.
  //    - If a contradiction is found, throw an exception.
  // 2. Choose a square and make a guess.
  //    a. Attempt to solve with that guess.
  //    b. If solving fails, eliminate that guess.
  //    c. Otherwise, return the puzzle.
  return puzzle;
}

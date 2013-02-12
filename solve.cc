#include "solve.h"

#include <stdexcept>

bool solved(const Puzzle& puzzle) {
  return true;
}

bool eliminate(Puzzle& puzzle) {
  return false;
}

void eliminate(Puzzle& puzzle, Square& guess) {
  
}

Square guess(const Puzzle& puzzle) {
  return Square();
}

Puzzle apply_guess(const Puzzle& puzzle, const Square& guess) {
  return puzzle;
}

Puzzle solve(Puzzle puzzle) {
  // While puzzle is not solved:
  while (!solved(puzzle)) {
    // 1. Run elimination until there are no changes.
    while (eliminate(puzzle));
    if (solved(puzzle))
      break;
    // 2. Choose a square and make a guess.
    Square sq = guess(puzzle);
    try {
      //    a. Attempt to solve with that guess.
      //    b. If solving succeeds, return the puzzle.
      return solve(apply_guess(puzzle, sq));
    } catch (std::invalid_argument) {
      //    c. Otherwise, eliminate that guess.
      eliminate(puzzle, sq);
    }
  }
  return puzzle;
}

#ifndef SOLVE_H_
#define SOLVE_H_

#include "puzzle.h"

// Solves a puzzle and returns the solution.
// Throws an invalid_argument exception if the puzzle is not solvable.
Puzzle solve_puzzle(const Puzzle& puzzle);

#endif

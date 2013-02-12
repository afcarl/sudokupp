#ifndef SOLVE_H_
#define SOLVE_H_

#include "puzzle.h"

// Solves a puzzle and returns the solution.
// Throws an invalid_argument exception if the puzzle is not solvable.
Puzzle solve_puzzle(const Puzzle& puzzle);

// Determines whether a puzzle is solved.
bool solved(const Puzzle& puzzle);

// Run elimination on a puzzle.
// Returns true if the puzzle was modified and false otherwise.
// Throws an invalid_argument exception if a contradiction is found.
bool eliminate(Puzzle& puzzle);

// Choose a square and guess its value.
Square guess(const Puzzle& puzzle);

#endif

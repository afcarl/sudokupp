#ifndef SOLVE_H_
#define SOLVE_H_

#include "puzzle.h"

// Solves a puzzle and returns the solution.
// Throws an invalid_argument exception if the puzzle is not solvable.
Puzzle solve(Puzzle puzzle);

// Determines whether a puzzle is solved.
// Throws an invalid_argument exception if a contradiction is found.
bool solved(const Puzzle& puzzle);

// Run elimination on a puzzle.
// Returns true if the puzzle was modified and false otherwise.
// Throws an invalid_argument exception if a contradiction is found.
bool eliminate(Puzzle& puzzle);

// Repeatedly applies elimination to a puzzle until it becomes stable,
// i.e. no further changes are possible.  Returns true if any changes
// were made and false otherwise.
bool eliminate_to_stable(Puzzle& puzzle);

// Run elimination on a particular square.
// Returns true if the puzzle was modified and false otherwise.
// Throws an invalid_argument exception if a contradiction is found.
bool eliminate(Puzzle& puzzle, int row, int col);

// Eliminate a possible value from a square.
void eliminate(Puzzle& puzzle, const Square& guess);
bool eliminate(Puzzle& puzzle, int row, int col, int val);

// Choose a square and guess its value.
Square guess(const Puzzle& puzzle);

// Apply a guess to a puzzle and return the resulting board.
Puzzle apply_guess(const Puzzle& puzzle, const Square& guess);

// Private:
bool sq_order(const Square& left, const Square& right);
bool row_full(Row row);
bool col_full(const Puzzle& puzzle, int col);
bool group_full(const Puzzle& puzzle, int x, int y);
bool eliminate_row(Puzzle& puzzle, int row, int col);
bool eliminate_column(Puzzle& puzzle, int row, int col);
bool eliminate_group(Puzzle& puzzle, int row, int col);

#endif

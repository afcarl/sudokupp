CXX=clang++

.PHONY: all clean

all: sudoku

clean:
	rm -rf *.o sudoku

solve_tests: tests.o puzzle.o solve.o solve_tests.o
	$(CXX) tests.o puzzle.o solve.o solve_tests.o -o solve_tests

sudoku: main.o puzzle.o solve.o
	$(CXX) main.o puzzle.o solve.o -o sudoku

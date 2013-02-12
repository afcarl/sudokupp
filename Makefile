CXX=clang++

.PHONY: all clean test

all: sudoku

clean:
	rm -rf *.o sudoku

tests: tests.o solve_tests.o
	$(CXX) tests.o solve_tests.o -o run_tests

test: tests
	./run_tests

sudoku: main.o puzzle.o solve.o
	$(CXX) main.o puzzle.o solve.o -o sudoku

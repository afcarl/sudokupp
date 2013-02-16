CXX=clang++
FLAGS=-g

.PHONY: all clean

all: sudoku

clean:
	rm -rf *.o sudoku solve_tests

%.o: %.cc
	$(CXX) $(FLAGS) -c $*.cc -o $@

solve_tests: tests.o puzzle.o solve.o solve_tests.o
	$(CXX) $(FLAGS) tests.o puzzle.o solve.o solve_tests.o -o solve_tests

sudoku: main.o puzzle.o solve.o
	$(CXX) $(FLAGS) main.o puzzle.o solve.o -o sudoku

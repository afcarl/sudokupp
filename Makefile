CXX=clang++

.PHONY: all clean

all: sudoku

clean:
	rm -rf *.o sudoku

sudoku: main.o puzzle.o solve.o
	$(CXX) main.o puzzle.o solve.o -o sudoku

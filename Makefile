CXX=clang++

.PHONY: all clean

all: sudoku

clean:
	rm -rf *.o sudoku

sudoku: main.o board.o
	$(CXX) main.o board.o -o sudoku

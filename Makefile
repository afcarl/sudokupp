CXX=clang++

.PHONY: all clean

all: sudoku

clean:
	rm -rf *.o sudoku

sudoku: main.o
	$(CXX) main.o -o sudoku

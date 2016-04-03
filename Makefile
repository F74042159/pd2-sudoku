all: Sudoku.o giveQuestion.o solve.o transform.o
	g++ -o giveQuestion giveQuestion.o Sudoku.o
	g++ -o solve solve.o Sudoku.o
	g++ -o transform transform.o Sudoku.o
giveQuestion.o:
	g++ -c giveQuestion.cpp

solve.o:
	g++ -c solve.cpp

transform.o:
	g++ -c transform.cpp

Sudoku.o: Sudoku.cpp Sudoku.h
	g++ -c Sudoku.cpp

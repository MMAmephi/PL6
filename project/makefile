all: sudoku clean clear

sudoku: main.o Grid.o CompleteSearch.o OptimisedSearch.o Generator.o templates.o Interface.o Game.o
	g++ -lncurses main.o Grid.o CompleteSearch.o OptimisedSearch.o Generator.o templates.o Interface.o Game.o -lstdc++fs -o sudoku

main.o: main.cpp
	g++ -c main.cpp -o main.o

Grid.o: Grid.cpp
	g++ -c Grid.cpp -o Grid.o

CompleteSearch.o: CompleteSearch.cpp
	g++ -c CompleteSearch.cpp -o CompleteSearch.o

OptimisedSearch.o: OptimisedSearch.cpp
	g++ -c OptimisedSearch.cpp -o OptimisedSearch.o

Generator.o: Generator.cpp
	g++ -c Generator.cpp -o Generator.o

templates.o: templates.cpp
	g++ -c templates.cpp -o templates.o

Interface.o: Interface.cpp
	g++ -c Interface.cpp -o Interface.o

Game.o: Game.cpp
	g++ -c Game.cpp -o Game.o

clean:
	rm -rf *.o

clear:
	clear

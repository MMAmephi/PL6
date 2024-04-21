all: task2 clean

task2: main.o Matrix.o
	g++ main.o Matrix.o -o task2

main.o: main.cpp
	g++ -c main.cpp -o main.o

Matrix.o: Matrix.cpp
	g++ -c Matrix.cpp -o Matrix.o

clean:
	rm -rf *.o

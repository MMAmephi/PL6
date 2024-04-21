all: task3 clean

task3: Node.o Edge.o Graph.o main.o
	g++ Node.o Edge.o Graph.o main.o -o task3

Node.o: Node.cpp
	g++ -c Node.cpp -o Node.o

Edge.o: Edge.cpp
	g++ -c Edge.cpp -o Edge.o

Graph.o: Graph.cpp
	g++ -c Graph.cpp -o Graph.o

main.o: main.cpp
	g++ -c main.cpp -o main.o

clean:
	rm -rf *.o

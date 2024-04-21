#include "Graph.h"
#include <iostream>

using namespace std;



void randomCheck_start_end(){
    srand(time(0));
    int numVertices = 20;
    Graph graph(numVertices);

    for(int i = 0; i < numVertices; i++){
        graph.addNode(i);
    }

    for(int i = 0; i < rand()%(numVertices) + 3*numVertices; i++){
        int n1 = rand()%numVertices;
        int n2 = rand()%numVertices;
        while(n1 == n2){
            n1 = rand()%numVertices;
            n2 = rand()%numVertices;   
        }
        graph.addEdge(n1, n2, rand()%10);
    }

    cout << "Randomly generated graph(startVertex and endVertex): " << endl;
    //graph.printGraph();
    //cout << endl;
    //graph.printAdjMatrix();
    //cout << endl;
    
    int startVertex = rand()%numVertices;
    int endVertex = rand()%numVertices;
    while(endVertex == startVertex){
	    endVertex = rand()%numVertices;
    }
    graph.printShortestPath_end(startVertex, endVertex);    
}


void randomCheck_start(){
    srand(time(0));
    int numVertices = 20;
    Graph graph(numVertices);

    for(int i = 0; i < numVertices; i++){
        graph.addNode(i);
    }

    for(int i = 0; i < rand()%(numVertices) + 3*numVertices; i++){
        int n1 = rand()%numVertices;
        int n2 = rand()%numVertices;
        while(n1 == n2){
            n1 = rand()%numVertices;
            n2 = rand()%numVertices;   
        }
        graph.addEdge(n1, n2, rand()%10);
    }

    cout << "Randomly generated graph(only startVertex): " << endl;
    //graph.printGraph();
    //cout << endl;
    //graph.printAdjMatrix();
    //cout << endl;
    
    int startVertex = rand()%numVertices;
    graph.printShortestPath(startVertex);    
}


int main() {
    randomCheck_start_end();
    randomCheck_start();
    return 0;
}

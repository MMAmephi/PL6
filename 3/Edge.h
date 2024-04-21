#ifndef EDGE_H
#define EDGE_H
using namespace std;

class Node; // Forward declaration

class Edge {
public:
    Node* node1;
    Node* node2;
    int weight;

    Edge(Node* n1, Node* n2, int w);
    ~Edge();
};

#endif
#include "Edge.h"
using namespace std;

Edge::Edge(Node* n1, Node* n2, int w) {
    node1 = n1;
    node2 = n2;
    weight = w;
}

Edge::~Edge() {
    node1 = nullptr;
    node2 = nullptr;
}
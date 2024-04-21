#ifndef NODE_H
#define NODE_H

#include <vector>
using namespace std;

class Node {
public:
    int number;
    vector<Node*> connectedNodes;

    Node(int num);
    ~Node();
};

#endif
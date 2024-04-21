#include "Node.h"
using namespace std;

Node::Node(int num) {
    number = num;
}

Node::~Node() {
    connectedNodes.clear();
}
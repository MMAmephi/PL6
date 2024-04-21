#include "Graph.h"
#include <iostream>
#include <limits.h>

using namespace std;


Graph::Graph(int numVertices) {
    this->numVertices = numVertices;
    adjMatrix.resize(numVertices, vector<int>(numVertices, 0));
    nodes.resize(numVertices);
}

Graph::Graph(vector<Edge*> edgeList, int numVertices) {
    this->numVertices = numVertices;
    adjMatrix.resize(numVertices, vector<int>(numVertices, 0));
    nodes.resize(numVertices);

    for (int i = 0; i < numVertices; i++) {
        Node* node = new Node(i);
        nodes[i] = node;
    }

    for (int i = 0; i < edgeList.size(); i++) {
        Edge* edge = edgeList[i];
        int src = edge->node1->number;
        int dest = edge->node2->number;
        int weight = edge->weight;

        adjMatrix[src][dest] = weight;
        adjMatrix[dest][src] = weight;

        nodes[src]->connectedNodes.push_back(nodes[dest]);
        nodes[dest]->connectedNodes.push_back(nodes[src]);

        edges.push_back(edge);
    }
}
Graph::Graph() {
        numVertices = 3;
        adjMatrix.resize(numVertices, vector<int>(numVertices, 0));
        nodes.resize(numVertices);

        for (int i = 0; i < numVertices; i++) {
            Node* node = new Node(i);
            nodes[i] = node;
        }

        addEdge(0, 1, 1);
        addEdge(0, 2, 1);
        addEdge(2, 1, 1);
}

Graph::Graph(const Graph& other) {
        numVertices = other.numVertices;
        adjMatrix = other.adjMatrix;

        for (int i = 0; i < numVertices; i++) {
            Node* node = new Node(*other.nodes[i]);
            nodes.push_back(node);
        }

        for (int i = 0; i < other.edges.size(); i++) {
            Edge* edge = other.edges[i];
            int src = edge->node1->number;
            int dest = edge->node2->number;
            int weight = edge->weight;

            Node* node1 = nodes[src];
            Node* node2 = nodes[dest];


            Edge* newEdge = new Edge(node1, node2, weight);

            edges.push_back(newEdge);

            node1->connectedNodes.push_back(node2);
            node2->connectedNodes.push_back(node1);
        }
    }

Graph::~Graph() {
    for (int i = 0; i < numVertices; i++) {
        delete nodes[i];
    }
    nodes.clear();

    for (int i = 0; i < edges.size(); i++) {
        delete edges[i];
    }
    edges.clear();
}

void Graph::clear() {
    for (auto node : nodes) {
        delete node;
    }
    nodes.clear();

    for (auto edge : edges) {
        delete edge;
    }
    edges.clear();
}

void Graph::addNode(int num) {
    Node* node = new Node(num);
    nodes[num] = node;
}

void Graph::addEdge(int src, int dest, int weight) {
    adjMatrix[src][dest] = weight;
    adjMatrix[dest][src] = weight;

    Node* node1 = nodes[src];
    Node* node2 = nodes[dest];

    Edge* edge = new Edge(node1, node2, weight);
    edges.push_back(edge);

    node1->connectedNodes.push_back(node2);
    node2->connectedNodes.push_back(node1);
}

void Graph::removeEdge(int src, int dest) {
    adjMatrix[src][dest] = 0;
    adjMatrix[dest][src] = 0;

    Node* node1 = nodes[src];
    Node* node2 = nodes[dest];

    for (auto it = edges.begin(); it != edges.end(); ++it) {
        Edge* edge = *it;
        if (edge->node1 == node1 && edge->node2 == node2) {
            delete edge;
            edges.erase(it);
            break;
        }
    }

    for (auto it = node1->connectedNodes.begin(); it != node1->connectedNodes.end(); ++it) {
        Node* connectedNode = *it;
        if (connectedNode == node2) {
            node1->connectedNodes.erase(it);
            break;
        }
    }

    for (auto it = node2->connectedNodes.begin(); it != node2->connectedNodes.end(); ++it) {
        Node* connectedNode = *it;
        if (connectedNode == node1) {
            node2->connectedNodes.erase(it);
            break;
        }
    }
}

void Graph::removeEdge(Edge* edge) {
    Node* node1 = edge->node1;
    Node* node2 = edge->node2;

    adjMatrix[node1->number][node2->number] = 0;
    adjMatrix[node2->number][node1->number] = 0;

    for (auto it = edges.begin(); it != edges.end(); ++it) {
        Edge* e = *it;
        if (e == edge) {
            delete e;
            edges.erase(it);
            break;
        }
    }

    for (auto it = node1->connectedNodes.begin(); it != node1->connectedNodes.end(); ++it) {
        Node* connectedNode = *it;
        if (connectedNode == node2) {
            node1->connectedNodes.erase(it);
            break;
        }
    }

    for (auto it = node2->connectedNodes.begin(); it != node2->connectedNodes.end(); ++it) {
        Node* connectedNode = *it;
        if (connectedNode == node1) {
            node2->connectedNodes.erase(it);
            break;
        }
    }
}

void Graph::printGraph() {
    for (int i = 0; i < numVertices; i++) {
        cout << "Node " << nodes[i]->number << " is connected to: ";
        for (int j = 0; j < nodes[i]->connectedNodes.size(); j++) {
            cout << nodes[i]->connectedNodes[j]->number << " ";
        }
        cout << endl;
    }
}

void Graph::printAdjMatrix() {
    cout << "   ";
    for (int i = 0; i < numVertices; i++) {
        cout << i << " ";
    }
    cout << endl;

    for (int i = 0; i < numVertices; i++) {
        cout << i << ": ";
        for (int j = 0; j < numVertices; j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::backtrack(vector<int>& path, vector<bool>& visited, int& minDist, vector<int>& minPath, int currDist) {
    if (path.size() == numVertices) {
        if (currDist > minDist) {
            minDist = currDist;
            minPath = path;
        }
        return;
    }

    int lastNode = path.back();

    for (int i = 0; i < numVertices; ++i) {
        if (!visited[i] && adjMatrix[lastNode][i] != 0) {
            currDist += adjMatrix[lastNode][i];
            path.push_back(i);
            visited[i] = true;

            backtrack(path, visited, minDist, minPath, currDist);

            visited[i] = false;
            path.pop_back();
            currDist -= adjMatrix[lastNode][i];
        }
    }
}

void Graph::backtrack_end(vector<int>& path, vector<bool>& visited, int& minDist, vector<int>& minPath, int currDist, int endVertex) {
    if (path.size() == numVertices && path.back() == endVertex) {
        if (currDist > minDist) {
            minDist = currDist;
            minPath = path;
        }
        return;
    }

    int lastNode = path.back();

    for (int i = 0; i < numVertices; ++i) {
        if (!visited[i] && adjMatrix[lastNode][i] != 0) {
            currDist += adjMatrix[lastNode][i];
            path.push_back(i);
            visited[i] = true;

            backtrack_end(path, visited, minDist, minPath, currDist, endVertex);

            visited[i] = false;
            path.pop_back();
            currDist -= adjMatrix[lastNode][i];
        }
    }
}

vector<int> Graph::findShortestPath(int startVertex) {
    vector<int> path, minPath;
    vector<bool> visited(numVertices, false);
    int minDist = INT_MIN;
    int currDist = 0;

    path.push_back(startVertex);
    visited[startVertex] = true;

    backtrack(path, visited, minDist, minPath, currDist);

    minPath.push_back(minDist);
    return minPath;
}

void Graph::printShortestPath(int startVertex){
    vector<int> path = this->findShortestPath(startVertex);
    if(path.back() == INT_MIN){
        cout << "There is no way to go through all the vertexes from " << startVertex << endl;
        return;
    }
    else{
        cout << "Longest path from vertex " << startVertex << ": ";
        for(int i = 0; i < path.size() - 1; i++){
            cout << path[i] << " ";
        }
        cout << endl <<  "Max Distance: " << path.back() << endl; 
    }
}

vector<int> Graph::findShortestPath_end(int startVertex, int endVertex) {
    vector<int> path, minPath;
    vector<bool> visited(numVertices, false);
    int minDist = INT_MIN;
    int currDist = 0;

    path.push_back(startVertex);
    visited[startVertex] = true;

    backtrack_end(path, visited, minDist, minPath, currDist, endVertex);

    minPath.push_back(minDist);
    return minPath;
}

void Graph::printShortestPath_end(int startVertex,int endVertex){
    vector<int> path = this->findShortestPath_end(startVertex, endVertex);
    if(path.back() == INT_MIN){
        cout << "There is no way to go through all the vertexes from " << startVertex << " to " << endVertex << endl;
        return;
    }
    else{
        cout << "Longest path from vertex " << startVertex << " to " << endVertex << ": ";
        for(int i = 0; i < path.size() - 1; i++){
            cout << path[i] << " ";
        }
        cout << endl <<  "Max Distance: " << path.back() << endl; 
    }
}

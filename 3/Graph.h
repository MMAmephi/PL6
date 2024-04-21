#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Node.h"
#include "Edge.h"
#include <vector>

using namespace std;

class Graph {
private:
    int numVertices;
    vector<vector<int>> adjMatrix;
    vector<Node*> nodes;
    vector<Edge*> edges;

public:
    Graph(int numVertices);
    Graph(vector<Edge*> edgeList, int numVertices);
    Graph();
    Graph(const Graph& other);
    ~Graph();

    void clear();
    void addNode(int num);
    void addEdge(int src, int dest, int weight);
    void removeEdge(int src, int dest);
    void removeEdge(Edge* edge);
    void printGraph();
    void printAdjMatrix();
    vector<int> findShortestPath(int startVertex);
    void printShortestPath(int startVertex);
    vector<int> findShortestPath_end(int startVertex, int endVertex);
    void printShortestPath_end(int startVertex, int endVertex);
private:
    void backtrack(vector<int>& path, vector<bool>& visited, int& minDist, vector<int>& minPath, int currDist);
    void backtrack_end(vector<int>& path, vector<bool>& visited, int& minDist, vector<int>& minPath, int currDist, int endVertex);
};

#endif

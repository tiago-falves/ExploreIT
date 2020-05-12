#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include "Node.h"
#include "MutablePriorityQueue.h"

using namespace std;



class Graph
{
private:
    unordered_map<long,Node*> nodes;
    void initNodes(Node *origin,Node *target);
    bool relax(Node *v,Node *w, double weight,long int targetDistance);
    void DFSVisit(Node *v);

public:
    vector<Node> pointsToDraw;
    double min_x=8000000000000.0;
    double max_x=-800000000000.0;
    double min_y=8000000000000.0;
    double max_y=-800000000000.0;


    unordered_map<long,Node*> getNodes();
    vector<Node> getPath(long int origin,long int dest);
    Node *findNode(const int &id) const;
    bool addNode(const int &id, int x, int y);
    bool addEdge(int origId, int destId);
    void printMatrix(double** matrix);
    void resetVisited();

    //Algorithms
    void DFSConnectivity(int id);
    void FloydWarshall();
    double Dijkstra(long int origin,long int  target,long int targetDistance);


    void removeUnvisited(Graph *graph);
    void removeSymetricEdges(int id);
    Edge *getSymetricEdge(Edge *edge);

};


#endif // GRAPH_H

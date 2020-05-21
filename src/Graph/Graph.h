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
#include <unordered_set>
#include "Node.h"
#include "MutablePriorityQueue.h"

using namespace std;



class Graph
{
private:
    unordered_map<long,Node*> nodes;
    unordered_map<long,Edge*> edges;
    vector<unordered_set<int>> graphs;
    vector<vector<int>> graphsVector;
    unordered_map<int,int> edgeDiff;
    void initNodes(Node *origin,Node *target);
    bool relax(Node *v,Node *w, double weight,long int targetDistance, int edge_difficulty, int difficulty);
    void DFSVisit(Node *v);

    //FLoyd Warshall matrices
    double ** W;   // dist
    double **P;   // path
public:
    unordered_map<int,int> getEdgeDiff();
    void setEdgeDiff(const unordered_map<int,int> edgeDiff);
    void setGraphs(const vector<unordered_set<int>> &graphs);
    const vector<vector<int>> &getGraphsVector() const;
    void setGraphsVector(const vector<vector<int>> &graphsVector);


    vector<vector<Node>> pointsToDraw;
    double min_x=8000000000000.0;
    double max_x=-800000000000.0;
    double min_y=8000000000000.0;
    double max_y=-800000000000.0;

    const unordered_map<long,Edge*> getEdges();
    void setEdges(const unordered_map<long, Edge*> edges);
    unordered_map<long,Node*> getNodes();
    vector<unordered_set<int>> getGraphs();
    vector<Node> getPath(long int origin,long int dest);
    Node *findNode(const int &id) const;
    bool addNode(const int &id, int x, int y);
    bool addEdgeDiff(const int &id, int diff);
    bool addEdge(int edgeId,int origId, int destId);
    Edge *findEdge(Node orig, Node dest);
    Edge *findEdge(const int &id) const;
    void printMatrix(double** matrix, ostream& ostream);
    void resetVisited();
    bool difficultyRange(int difficulty, int edge_difficulty);
    int getNodeDistance(int origid, int destid);

    //Algorithms
    void DFSConnectivity(int id);
    void FloydWarshall(string directory);
    double AStar(long int origin,long int  target,long int targetDistance, int difficulty);


    void removeUnvisited(Graph *graph);
    void removeSymetricEdges(int id);
    Edge *getSymetricEdge(Edge *edge);

    int getMostConnected();

    bool calculateInterestingPath(vector<int> confluencePoints, vector<int> hours, vector<int> difficulties, int TMax);

    int getNodeConnectedGraph(int node);

    bool isInConnectedGraph(int index, int node);

    void dijkstraShortestPath(const int &source, const int &dest);

    bool relaxDijkstra(Node *node, Edge *edge);
};


#endif // GRAPH_H

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
    vector<Node*> nodesVector;
    unordered_map<long,Edge*> edges;
    vector<unordered_set<int>> graphs;
    vector<vector<int>> graphsVector;
    unordered_map<int,int> edgeDiff;
    vector<vector<int>> floydMatrix;
    bool hasFloyd = false;
    bool grid = false;
public:
    bool isGrid() const;

    void setGrid(bool grid);

private:

    //FLoyd Warshall matrices
    double ** W;   // dist
    double **P;   // path


    void initNodes(Node *origin,Node *target,vector<Node> *nodesVisited = nullptr);
    /**
     * A* algorithm heuristic that maximizes as much as possible the intended results.
     * @param v
     * @param w
     * @param weight
     * @param targetDistance
     * @param edge_difficulty
     * @param difficulty
     * @param withPoi
     * @return
     */
    bool relax(Node *v,Node *w, double weight,long int targetDistance, int edge_difficulty, int difficulty,bool withPoi = true);

    /**
     * Auxilary function for the DFS connectivity algorithm.
     * @param v
     */
    void DFSVisit(Node *v);

    /**
     * Different levels of difficulties for each group.
     */
    vector<int> selected_difficulties;

    /**
     * Number of confluence points.
     */
    int numOfConfluencePoints;

    /**
     * Calculates approximate distance between nodes needed for the algorithm's heuristic.
     * @param n1
     * @param n2
     * @return
     */
    float calculateDistance(int n1,int n2);

    /**
     * Defines hours of confluence for different confluence points.
     * @param finalVect
     * @param confluencePoints
     * @param hours
     */
    void defineHours(vector<int> finalVect,vector<int> confluencePoints,vector<int> &hours);
public:
    /**
     * Processes mandatory points of interest.
     * @param confluencePoints
     * @param mandatoryPOIS
     * @param hours
     * @param difficulties
     * @return
     */
    vector<int> mandatoryPOIS(vector<int> confluencePoints,vector<int> mandatoryPOIS,vector<int> hours, vector<int> difficulties);

    /**
     * Gets number of confluence points.
     * @return
     */
    int getNumOfConfluencePoints() const;

    /**
     * Sets number of confluence points.
     * @param numOfConfluencePoints
     */
    void setNumOfConfluencePoints(int numOfConfluencePoints);
    unordered_map<int,int> getEdgeDiff();
    void setEdgeDiff(const unordered_map<int,int> edgeDiff);

    /**
     * Sets strongly connected graphs.
     * @param graphs
     */
    void setGraphs(const vector<unordered_set<int>> &graphs);

    /**
     * Gets strongly connected graphs by grouping node's ids.
     * @return
     */
    const vector<vector<int>> &getGraphsVector() const;

    /**
     * Sets strongly connected graphs in vector of ids form.
     * @param graphsVector
     */
    void setGraphsVector(const vector<vector<int>> &graphsVector);
    const vector<vector<int>> &getFloydMatrix() const;

    /**
     * Sets Floyd Warshall algorithm matrix when loading from files.
     * @param floydMatrix
     */
    void setFloydMatrix(const vector<vector<int>> &floydMatrix);
    string path;

    /**
     * Indicates if Floyd Warshall data has been processed.
     * @return
     */
    bool isHasFloyd() const;

    /**
     * Sets indication if Floyd Warshall data has been processed.
     * @param hasFloyd
     */
    void setHasFloyd(bool hasFloyd);

    /**
     * Resulting nodes that will be part of the path that will be drawn as result.
     */
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
    bool addNode(const int &id, int x, int y,int position);
    bool addEdgeDiff(const int &id, int diff);
    bool addEdge(int edgeId,int origId, int destId);
    Edge *findEdge(Node orig, Node dest);
    Edge *findEdge(const int &id) const;
    void printMatrix(double** matrix, ostream& ostream);
    void resetVisited();
    bool difficultyRange(int difficulty, int edge_difficulty);
    int getNodeDistance(int origid, int destid);

    //Algorithms
    /**
     * DFS algorithm used for getting strongly connected graphs.
     * @param id
     */
    void DFSConnectivity(int id);

    /**
     * Floyd Warshall algorithm.
     * @param directory
     */
    void FloydWarshall(string directory);

    /**
     * Executes A* algorithm with given parameter AStarType that indicates situation where algorithm will be applied.
     * @param origin
     * @param target
     * @param targetDistance
     * @param difficulty
     * @param nodesVisited
     * @param AStarType
     * @return
     */
    double AStar(long int origin,long int  target,long int targetDistance, int difficulty,vector<Node> *nodesVisited = nullptr,string AStarType = "");

    /**
     * Removes unvisited graph after DFS algorithm execution.
     * @param graph
     */
    void removeUnvisited(Graph *graph);

    /**
     * Removes symetric edges.
     * @param id
     */
    void removeSymetricEdges(int id);

    /**
     * Gets edge in opposite direction from the edge given as parameter.
     * @param edge
     * @return
     */
    Edge *getSymetricEdge(Edge *edge);

    /**
     * Gets index of the strongly connected graph.
     * @return
     */
    int getMostConnected();

    /**
     * Function that calculates path for group with multiple points of interest
     * @param confluencePoints
     * @param hours
     * @param difficulties
     * @param TMax
     * @return
     */
    bool calculateInterestingPath(vector<int> confluencePoints, vector<int> hours, vector<int> difficulties, int TMax);

    /**
     * Gets strongly connected graph node belongs to.
     * @param node
     * @return
     */
    int getNodeConnectedGraph(int node);

    /**
     * Returns True if node belongs to strongly connected graph with index.
     * @param index
     * @param node
     * @return
     */
    bool isInConnectedGraph(int index, int node);

    void dijkstraShortestPath(const int &source, const int &dest);

    /**
     * Relax function for the Dijkstra algorithm
     * @param node
     * @param edge
     * @return
     */
    bool relaxDijkstra(Node *node, Edge *edge);

    void setSelectedDiff(vector<int> selected_difficulties){this->selected_difficulties = selected_difficulties;}
    vector<int> getSelectedDiff() {return selected_difficulties;}

    /**
     * Gets Heuristic function to apply depending on the iteration that is being executed.
     * @param v
     * @param w
     * @param tam_edge
     * @param targetDistance
     * @param edge_difficulty
     * @param difficulty
     * @param type Indicates type of iteration that is being executed.
     * @return
     */
    bool getRelaxFunction(Node *v, Node *w, double tam_edge, long targetDistance, int edge_difficulty, int difficulty,string type);

    /**
     * A* algorithm heuristic that only takes distances and difficulties into consideration.
     * @param v
     * @param w
     * @param tam_edge
     * @param targetDistance
     * @param edge_difficulty
     * @return
     */
    bool relaxDistance(Node *v, Node *w, double tam_edge, long targetDistance,int edge_difficulty);
};


#endif // GRAPH_H

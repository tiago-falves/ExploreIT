//
// Created by tiago on 08/05/2020.
//

#include <string>
#include <chrono>
#include <fstream>
#include "GraphLoader.h"
#include "../../Utils/utils.h"
#include "../graph.h"
#include "Node.h"
#include "Position.h"

using namespace std;

bool GraphLoader::loadGraph(Graph<Node> * graph) {
    return (loadNodes(graph) && loadEdges(graph));
}
bool GraphLoader::loadNodes(Graph<Node> * graph) {

    int numberNodes, id;
    double x, y;
    char c;

    fstream file_node("../data/nodes.txt");
    if (!file_node.is_open())
    {
        cout << "Node File not found\n";
        return false;
    }

    file_node >> numberNodes;
    
    graph->min_x=8000000000000;
    graph->max_x=-800000000000;
    graph->min_y=8000000000000;
    graph->max_y=-800000000000;

    for (int i = 0; i < numberNodes; i++) {
        file_node >> c >> id >> c >> x >> c >> y >> c;
        graph->addVertex(Node(id, x, y));

        if(x>graph->max_x)
            graph->max_x=x;
        if(x<graph->min_x)
            graph->min_x=x;

        if(y>graph->max_y)
            graph->max_y=y;
        if(y<graph->min_y)
            graph->min_y=y;
        //cout << to_string(id) << " x:" << to_string(x) << "\n";
    }
    file_node.close();

    cout << "Ended Nodes\n";
    return true;

}


bool GraphLoader::loadEdges(Graph<Node> * graph) {
    int numberEdges, originId, destId;
    char c;

    ifstream edgesFile("../data/edges.txt");
    if (!edgesFile.is_open()) return false;
    cout << "Started Edges\n";
    edgesFile >> numberEdges;

    for (int i = 0; i < numberEdges; i++) {
        edgesFile >> c >> originId >> c >> destId >> c;
        Node tmp_n_o=graph->findVertex(Node(originId,0,0))->getInfo();
        Node tmp_n_d=graph->findVertex(Node(destId,0,0))->getInfo();

        double weight=Position(tmp_n_o.getX(),tmp_n_o.getY()).calculateRealDistance(Position(tmp_n_d.getX(),tmp_n_d.getY()));
        graph->addEdge(Node(originId,0,0),Node(destId,0,0),weight);
        graph->addEdge(Node(destId,0,0),Node(originId,0,0),weight);
    }

    edgesFile.close();

    cout << "Ended Edges\n";

    return true;
}

//
// Created by tiago on 08/05/2020.
//

#include <string>
#include <src/Graph/graph.h>
#include <chrono>
#include "GraphLoader.h"
#include "utils.h"

using namespace std;

bool GraphLoader::loadGraph(Graph * graph) {
    return (loadNodes(graph) && loadEdges(graph));
}
bool GraphLoader::loadNodes(Graph * graph) {

    int numberNodes, id;
    double x, y;
    char c;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    cout<<"Start!"<<endl;
    fstream file_node("../data/nodes.txt");
    if (!file_node.is_open())
    {
        cout << "Node File not found\n";
        return false;
    }

    file_node >> numberNodes;

    for (int i = 0; i < numberNodes; i++) {
        file_node >> c >> id >> c >> x >> c >> y >> c;
        graph->addNode(id, x, y);
        //cout << to_string(id) << " x:" << to_string(x) << "\n";
    }
    file_node.close();
    return true;

}


bool GraphLoader::loadEdges(Graph * graph) {
    int numberEdges, originId, destId;
    char c;

    ifstream edgesFile("../data/edges.txt");
    if (!edgesFile.is_open()) return false;

    edgesFile >> numberEdges;

    for (int i = 0; i < numberEdges; i++) {
        edgesFile >> c >> originId >> c >> destId >> c;
        graph->addEdge(originId, destId);
    }

    edgesFile.close();

    return true;
}
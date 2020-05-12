//
// Created by tiago on 08/05/2020.
//

#include <string>
#include <chrono>
#include "GraphLoader.h"
#include "../../Utils/utils.h"
#include "Graph.h"

using namespace std;

bool GraphLoader::loadGraph(Graph * graph, bool isTesting) {
    return (loadNodes(graph,isTesting) && loadEdges(graph,isTesting) && loadTags(graph,isTesting));
}


bool GraphLoader::loadNodes(Graph * graph, bool isTesting) {

    int numberNodes, id;
    double x, y;
    char c;
    fstream file_node;

    if(isTesting)  file_node.open("../data/nodes.txt");
    else file_node.open("../data/PortugalMaps/Aveiro/nodes_x_y_aveiro.txt");
    if (!file_node.is_open())
    {
        cout << "Node File not found\n";
        return false;
    }

    file_node >> numberNodes;

    for (int i = 0; i < numberNodes; i++) {
        file_node >> c >> id >> c >> x >> c >> y >> c;
        graph->addNode(id, x, y);
        //cout << to_string(id) << " x:" << to_string(x) << " y:" << to_string(y) << "\n";
        if(x>graph->max_x) graph->max_x=x;
        if(x<graph->min_x) graph->min_x=x;
        if(y>graph->max_y) graph->max_y=y;
        if(y<graph->min_y) graph->min_y=y;
    }
    file_node.close();

    cout << "Ended Nodes\n";
    return true;

}


bool GraphLoader::loadEdges(Graph * graph,bool isTesting) {
    int numberEdges, originId, destId;
    char c;

    ifstream edgesFile;

    if(isTesting)  edgesFile.open("../data/edges.txt");
    else edgesFile.open("../data/PortugalMaps/Aveiro/edges_aveiro.txt");

    if (!edgesFile.is_open()) return false;

    edgesFile >> numberEdges;

    int edgeId = 0;

    for (int i = 0; i < numberEdges; i++) {
        edgeId+=2;
        edgesFile >> c >> originId >> c >> destId >> c;
        graph->addEdge(edgeId,originId, destId);
    }
    edgesFile.close();

    return true;
}

bool GraphLoader::loadTags(Graph * graph,bool isTesting) {
    int totalTags, numberTags,nodeId;
    string tag;
    if(isTesting) return true;
    fstream TagsFile("../data/TagExamples/Aveiro/t03_tags_aveiro.txt"); //Turismo

    if (!TagsFile.is_open()) return false;

    TagsFile >> totalTags;

    for (int i = 0; i < totalTags; i++) {
        TagsFile >> tag >> numberTags;
        for (int j = 0; j < numberTags; ++j) {
            TagsFile >> nodeId;
            Node * node = graph->findNode(nodeId);
            if(node != nullptr) node->addTag(tag);
        }
    }
    TagsFile.close();

    return true;
}

bool GraphLoader::loadDifficulties(Graph * graph,string directory) {
    int edgeId, difficulty;
    char c;
    fstream diffFile(directory + "difficulties.txt");
    if (!diffFile.is_open()) return false;
    while (diffFile >> c >> edgeId >> c >> difficulty >> c){
        //GraphLoader::edgeDiff.insert(pair<int,int>(edgeId,difficulty));
    }
    diffFile.close();

    return true;
}



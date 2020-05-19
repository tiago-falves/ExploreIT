//
// Created by tiago on 08/05/2020.
//

#include <string>
#include <chrono>
#include "GraphLoader.h"
#include "../../Utils/utils.h"
#include "Graph.h"

using namespace std;


GraphLoader::GraphLoader(Graph * graph,const string &directory, const string &nodeFile, const string &edgeFile,const string &tagPath) :
    graph(graph), directory(directory), nodeFile(nodeFile), edgeFile(edgeFile),tagPath(tagPath) {
}


bool GraphLoader::loadGraph(bool isGrid) {
    return (loadNodes() && loadDifficulties() && loadEdges() && loadTags(isGrid));
}

bool GraphLoader::loadNodes( ) {
    cout << "\tLoading nodes\n";

    int numberNodes, id;
    double x, y;
    char c;
    ifstream file_node;

    file_node.open(directory + nodeFile);
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

    return true;

}


bool GraphLoader::loadEdges() {

    cout << "\tLoading Edges\n";

    int numberEdges, originId, destId;
    char c;

    ifstream file;

    file.open(directory + edgeFile);
    if (!file.is_open()){
        cout << "Error Opening edges file\n";
        return false;
    }

    file >> numberEdges;

    int edgeId = 0;

    for (int i = 0; i < numberEdges; i++) {
        int difficulty = 0;

        edgeId+=2;
        if(graph->getEdgeDiff().size()>0){
            difficulty = graph->getEdgeDiff().at(edgeId);
        }
        file >> c >> originId >> c >> destId >> c;
        graph->addEdge(edgeId,originId, destId,difficulty);
    }
    file.close();

    return true;
}

bool GraphLoader::loadTags(bool isTesting) {
    int totalTags, numberTags,nodeId;
    string tag;
    if(isTesting) return true;

    cout << "\tLoading Tags\n";


    ifstream TagsFile(tagPath); //Turismo

    if (!TagsFile.is_open()){
        cout << "Error Opening Tag file\n";
        return false;
    }

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

bool GraphLoader::loadDifficulties() {
    int edgeId, difficulty;
    char c;
    ifstream diffFile(directory + "difficulties.txt");
    if (!diffFile.is_open()){
        cout << "Error opening difficulties file, please preprocess\n";
        return false;
    }
    cout << "\tLoading Difficulties\n";


    while (diffFile >> c >> edgeId >> c >> difficulty >> c){
        graph->addEdgeDiff(edgeId,difficulty);
    }
    diffFile.close();
    return true;
}

bool GraphLoader::loadConnectivity() {

    vector<unordered_set<int>> graphs;
    vector<vector<int>> graphVector;
    int totalGraphs,numberNodes,nodeId;

    cout << "\tLoading Connectivity\n";

    ifstream file(connectivityFile);

    if (!file.is_open()){
        cout << connectivityFile << endl;
        cout << "Error Opening Connectivity file\n";
        return false;
    }

    file >> totalGraphs;

    for (int i = 0; i < totalGraphs; i++) {
        file >> numberNodes;
        unordered_set<int> nodes;
        vector<int> nodeVector;
        for (int j = 0; j < numberNodes; ++j) {
            file >> nodeId;
            nodes.insert(nodeId);
            nodeVector.push_back(nodeId);
        }
        graphs.push_back(nodes);
        graphVector.push_back(nodeVector);
    }
    file.close();

    graph->setGraphs(graphs);
    graph->setGraphsVector(graphVector);
    return true;
}

const string &GraphLoader::getDirectory() const {
    return directory;
}

void GraphLoader::setDirectory(const string &directory) {
    GraphLoader::directory = directory;
}

const string &GraphLoader::getNodeFile() const {
    return nodeFile;
}

void GraphLoader::setNodeFile(const string &nodeFile) {
    GraphLoader::nodeFile = nodeFile;
}

const string &GraphLoader::getEdgeFile() const {
    return edgeFile;
}

void GraphLoader::setEdgeFile(const string &edgeFile) {
    GraphLoader::edgeFile = edgeFile;
}

const string &GraphLoader::getConnectivityFile() const {
    return connectivityFile;
}

void GraphLoader::setConnectivityFile(const string &connectivityFile) {
    GraphLoader::connectivityFile = connectivityFile;
}





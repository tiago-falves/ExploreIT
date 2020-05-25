//
// Created by tiago on 12/05/2020.
//

#include "Preprocessor.h"

Preprocessor::Preprocessor(Graph *graph) : graph(graph) {}


void Preprocessor::preProcessDifficulties(){
    srand( time(NULL) );

    for(pair<long,Node *> node : graph->getNodes()) {
        for (Edge *edge :node.second->getEdges()) {
            int currentDifficulty = randomDifficultyCalculator(1);
            Edge * symetricEdge = graph->getSymetricEdge(edge);
            edge->setDifficulty(currentDifficulty);
            symetricEdge->setDifficulty(currentDifficulty);
        }
    }

}

void Preprocessor::preprocessConnectivity(string directory){

    ofstream myfile;
    myfile.open (directory + "connectivity.txt");
    vector<vector<int>> graphs = calculateConnectedGraphs();
    myfile << graphs.size() << endl;
    for (int i = 0; i < graphs.size(); ++i) {
        myfile <<graphs[i].size() << endl;
        for(int idNode : graphs[i]){
            myfile << idNode << endl;
        }
    }
    myfile.close();


}

vector<vector<int>> Preprocessor::calculateConnectedGraphs(){
    vector<vector<int>> result;
    graph->resetVisited();
    for(auto IDNode : graph->getNodes()){
        Node * node = IDNode.second;
        if(!node->visited){
            vector<int> connectedNodes;
            DFSVisit(node,connectedNodes);
            result.push_back(connectedNodes);
        }
    }
    return result;

}


void Preprocessor::DFSVisit(Node * node,vector<int> &connectedNodes) {
    node->visited = true;
    for (Edge * edge : node->getEdges()) {
        if (!edge->getDestination()->visited) {
            DFSVisit(edge->getDestination(),connectedNodes);
            connectedNodes.push_back(edge->getDestination()->getId());
        }
    }
}

int Preprocessor::randomDifficultyCalculator(int currentHeight){
    int diff = randomGenerator(1,10);
    bool turnSmaller = (rand() % 100) < 50;
    if(turnSmaller) {
        if (diff > 7) {
            diff = randomGenerator(1, 7);
        }
        if (diff > 4) {
            diff = randomGenerator(1, 4);
        }
    }
    return diff;
}

int Preprocessor::randomGenerator(int min, int max){
    return (rand() % max + min);
}

int Preprocessor::saveDifficulties(string directory){
    ofstream myfile;
    myfile.open (directory + "difficulties.txt");
    for(pair<long,Node *> node : graph->getNodes()) {
        for (Edge *edge :node.second->getEdges()) {
            myfile << "(" << edge->getId() << "," << edge->getDifficulty() << ")\n";
        }
    }
    myfile.close();
    return 0;
}

Graph *Preprocessor::getGraph() const {
    return graph;
}

void Preprocessor::setGraph(Graph *graph) {
    Preprocessor::graph = graph;
}

//Generating (int) (1/10 no nodes na grid)
void Preprocessor::setGridPOIs(int grid_type, string directory) {
    ofstream def; def.open(directory + "pois.txt");
    int n = (grid_type+1)*(grid_type+1);
    int nodeid;
    srand(time(0));
    for (int i = 0; i < n/10; i++){
        nodeid = randomGenerator(0, n-1);
        def << nodeid << endl;
    }
}



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




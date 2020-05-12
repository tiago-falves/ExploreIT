//
// Created by tiago on 12/05/2020.
//

#ifndef CAL1920_PREPROCESSOR_H
#define CAL1920_PREPROCESSOR_H


#include "Graph.h"

class Preprocessor {
private:
    Graph graph;

    static int randomGenerator(int min, int max);
    static int randomDifficultyCalculator(int currentHeight);
public:
    const Graph &getGraph() const;
    void setGraph(const Graph &graph);

    Preprocessor(const Graph &graph);

    static void preProcessDifficulties(Graph *graph);
};


#endif //CAL1920_PREPROCESSOR_H

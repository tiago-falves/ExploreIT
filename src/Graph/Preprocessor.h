//
// Created by tiago on 12/05/2020.
//

#ifndef CAL1920_PREPROCESSOR_H
#define CAL1920_PREPROCESSOR_H


#include "Graph.h"

class Preprocessor {
private:
    Graph * graph;
    static int randomGenerator(int min, int max);
    static int randomDifficultyCalculator(int currentHeight);
public:

    Preprocessor(Graph *graph);
    void preProcessDifficulties();
    int saveDifficulties(string directory);
    Graph *getGraph() const;
    void setGraph(Graph *graph);
    void setGridPOIs(int grid_type);
};


#endif //CAL1920_PREPROCESSOR_H

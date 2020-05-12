//
// Created by tiago on 08/05/2020.
//

#ifndef CAL1920_GRAPHDRAWER_H
#define CAL1920_GRAPHDRAWER_H

#include "graphviewer.h"


class GraphDrawer {
private:
    int width, height;
    GraphViewer * graphViewer;
public:
    void resetGraphViewer();
    void drawFromGraph(Graph *graph);
    GraphDrawer(int width, int height);

    string parseColor(string tag);

    void drawDifficulties(int edgeId, Edge *edge);
};


#endif //CAL1920_GRAPHDRAWER_H

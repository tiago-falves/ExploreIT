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

    void drawNodes(Graph * graph);

public:
    void resetGraphViewer();
    void drawFromGraph(Graph *graph);
    GraphDrawer(int width, int height);

    string parseColor(string tag);

    void drawDifficulties(int edgeId, Edge *edge);
    void drawDetailedDifficulties(int edgeId, Edge * edge);

    void drawDetailedThicknesses(int edgeId,Edge * edge);
    string getColor(int diff);

    void drawEdges(Graph *graph, int &cont);

    void drawPath(Graph *graph, int &cont);
};


#endif //CAL1920_GRAPHDRAWER_H

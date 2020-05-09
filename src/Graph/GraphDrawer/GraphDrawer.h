//
// Created by tiago on 08/05/2020.
//

#ifndef CAL1920_GRAPHDRAWER_H
#define CAL1920_GRAPHDRAWER_H

#include <Node.h>
#include "../../GraphViewer/cpp/graphviewer.h"


class GraphDrawer {
private:
    int width, height;
    GraphViewer * graphViewer;
public:
    void resetGraphViewer();
    void drawFromGraph(Graph<Node> *graph);
    GraphDrawer(int width, int height);
};


#endif //CAL1920_GRAPHDRAWER_H

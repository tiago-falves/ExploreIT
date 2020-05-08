//
// Created by tiago on 08/05/2020.
//

#include "../graph.h"
#include "GraphDrawer.h"

GraphDrawer::GraphDrawer(int width, int height) {
    this->width = width;
    this->height = height;
    //this->graphViewer = new GraphViewer(width, height,false);
}

/*void GraphDrawer::resetGraphViewer() {
    graphViewer->closeWindow();
    delete graphViewer;
    graphViewer = new GraphViewer(width, height, false);
}

void GraphDrawer::drawFromGraph(Graph * graph){
    resetGraphViewer();
    graphViewer->createWindow(width,height);
    graphViewer->defineVertexSize(1);

}*/
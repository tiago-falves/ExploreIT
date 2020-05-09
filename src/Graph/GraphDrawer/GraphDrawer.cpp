//
// Created by tiago on 08/05/2020.
//

#include "../graph.h"
#include "GraphDrawer.h"

GraphDrawer::GraphDrawer(int width, int height) {
    this->width = width;
    this->height = height;
    this->graphViewer = new GraphViewer(width, height, false);
}

void GraphDrawer::resetGraphViewer() {
    graphViewer->closeWindow();
    delete graphViewer;
    graphViewer = new GraphViewer(width, height, false);
}

void GraphDrawer::drawFromGraph(Graph * graph) {
    int i = 0;
    resetGraphViewer();
    graphViewer->createWindow(width, height);
    graphViewer->defineEdgeDashed(0);
    graphViewer->defineEdgeCurved(0);
    graphViewer->defineVertexSize(1);
    float min_x=8000000000000;
    float max_x=-800000000000;
    float min_y=8000000000000;
    float max_y=-800000000000;

    for (auto node:graph->getNodes()) {
        graphViewer->addNode(node.second->getId(),
                             (node.second->getX()-520106.0)/(40512-20106)*1990+5,
                             (node.second->getY()-4486780.0)/(507560-486780)*1990+5
        );
        if(node.second->getX()>max_x)
            max_x=node.second->getX();
        if(node.second->getX()<min_x)
            min_x=node.second->getX();

        if(node.second->getY()>max_y)
            max_y=node.second->getY();
        if(node.second->getY()<min_y)
            min_y=node.second->getY();


    }
    for (auto node:graph->getNodes())
        for(auto edge:node.second->getEdges()){
            graphViewer->addEdge(++i,edge->getOrigin()->getId(),edge->getDestination()->getId(),EdgeType::UNDIRECTED);
            graphViewer->setEdgeColor(i,"blue");
        }
    cout<<max_x<<" "<<min_x<<endl;
    cout<<max_y<<" "<<min_y<<endl;
    graphViewer->rearrange();
}
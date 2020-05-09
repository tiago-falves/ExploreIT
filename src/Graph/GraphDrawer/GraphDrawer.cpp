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

void GraphDrawer::drawFromGraph(Graph<Node> * graph) {
    cout<<"entrei"<<endl;
    int i = 0;
    resetGraphViewer();
    graphViewer->createWindow(width, height);
    graphViewer->defineEdgeDashed(0);
    graphViewer->defineEdgeCurved(0);
    graphViewer->defineVertexSize(1);


    for (auto node:graph->getVertexSet()) {
        graphViewer->
        addNode(
                node->getInfo().getId(),
                (node->getInfo().getX()-graph->min_x)/(graph->max_x-graph->min_x)*1990+5,
                (node->getInfo().getY()-graph->min_y)/(graph->max_y-graph->min_y)*1990+5);
    }
    Node a=Node(40,0,0);
    Node b=Node(200,0,0);
    auto tmp = graph->getPath(a,b);
    cout<<"ola: "<<tmp.size()<<endl;

    for(int it=0;it<tmp.size()-1;it++)
        graphViewer->addEdge(++i,tmp.at(it).getId(),tmp.at(it+1).getId(),EdgeType::UNDIRECTED);
    graphViewer->rearrange();
}

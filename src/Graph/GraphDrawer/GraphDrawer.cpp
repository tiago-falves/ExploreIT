//
// Created by tiago on 08/05/2020.
//

//#include <zconf.h>
#include <Utils/utils.h>
#include "Graph.h"
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

    resetGraphViewer();
    graphViewer->createWindow(width, height);
    graphViewer->defineEdgeDashed(0);
    graphViewer->defineEdgeCurved(0);
    graphViewer->defineVertexSize(0.1);

    int minX = graph->min_x, y_offset = 0;

    int cont = 0;
    //for (auto node:graph->getNodes()) {
    for(pair<long,Node *> node : graph->getNodes()){
        graphViewer->addNode(node.second->getId(),
                             (node.second->getX()-graph->min_x)/(graph->max_x-graph->min_x)*1990+5,
                             (node.second->getY()-graph->min_y)/(graph->max_y-graph->min_y)*1990+5
        );
        if(node.second->getTags().size() != 0) {
            graphViewer->setVertexColor(node.second->getId(), parseColor(node.second->getTags()[0]));
        }
    }
    for(pair<long,Node *> node : graph->getNodes()) {
        for (Edge *edge :node.second->getEdges()) {
            graphViewer->addEdge(cont, node.first, edge->getDestination()->getId(), EdgeType::UNDIRECTED);
            cont++;
        }
    }

    graphViewer->setVertexColor(graph->pointsToDraw.front()(),"red");
    graphViewer->setVertexColor(graph->pointsToDraw.back()(),"blue");

    for(int it=0;it<graph->pointsToDraw.size()-1;it++){
        graphViewer->addEdge(++cont,graph->pointsToDraw.at(it+1)(),graph->pointsToDraw.at(it)(),EdgeType::DIRECTED);
    }
    graphViewer->rearrange();
    sleep(1000);

}
string GraphDrawer::parseColor(string tag){

    string tagType;
    std::string::size_type pos = tag.find('=');
    if (pos != std::string::npos) tagType = tag.substr(0, pos);

    if(tagType == "tourism") return "orange";
    return "yellow";
}




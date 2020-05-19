//
// Created by tiago on 08/05/2020.
//

#include <Utils/utils.h>
#include <zconf.h>
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

    cout << "Drawing Graph...\n";
    resetGraphViewer();
    graphViewer->createWindow(width, height);
    graphViewer->defineEdgeDashed(0);
    graphViewer->defineEdgeCurved(0);
    graphViewer->defineVertexSize(0.1);


    int cont = 0;
    drawNodes(graph);
    drawEdges(graph,cont);
    drawPath(graph,cont);
    cout << "Ended Drawing\n";

    graphViewer->rearrange();


    sleep(1000);



}


void GraphDrawer::drawNodes(Graph * graph){
    cout << "\tDrawing Nodes...\n";


    for(pair<long,Node *> node : graph->getNodes()){

        graphViewer->addNode(node.second->getId(),
                             (node.second->getX()-graph->min_x)/(graph->max_x-graph->min_x)*1990+5,
                             (node.second->getY()-graph->min_y)/(graph->max_y-graph->min_y)*1990+5
        );

        if(node.second->getTags().size() != 0) {
            graphViewer->setVertexColor(node.second->getId(), parseColor(node.second->getTags()[0]));
        }
    }
    graphViewer->setVertexColor(graph->pointsToDraw.front()(),"red");
    graphViewer->setVertexColor(graph->pointsToDraw.back()(),"blue");
}

void GraphDrawer::drawEdges(Graph *graph,int &cont) {
    cout << "\tDrawing Edges...\n";

    for(pair<long,Node *> node : graph->getNodes()) {
        for (Edge *edge :node.second->getEdges()) {
            graphViewer->addEdge(cont, node.first, edge->getDestination()->getId(), EdgeType::UNDIRECTED);
            drawDifficulties(cont,edge);
            cont++;
        }
    }
}

void GraphDrawer::drawPath(Graph *graph, int &cont) {
    cout << "\tDrawing Path...\n" << graph->pointsToDraw.size();

    for(int it=0;it<graph->pointsToDraw.size()-1;it++){
        cout << it << endl;
        Node orig = graph->pointsToDraw.at(it+1);
        Node dest = graph->pointsToDraw.at(it);
        graphViewer->addEdge(cont,orig(),dest(),EdgeType::DIRECTED);
        drawDetailedDifficulties(cont,graph->findEdge(orig, dest));
        cont++;
    }
}

string GraphDrawer::parseColor(string tag){
    string tagType;
    std::string::size_type pos = tag.find('=');
    if (pos != std::string::npos) tagType = tag.substr(0, pos);

    if(tagType == "tourism") return "orange";
    return "yellow";
}

void GraphDrawer::drawDifficulties(int edgeId,Edge * edge){
    if(edge->getDifficulty() < 2) graphViewer->setEdgeColor(edgeId, GREEN);
    else if(edge->getDifficulty() < 6) graphViewer->setEdgeColor(edgeId, BLUE);
    else graphViewer->setEdgeColor(edgeId, RED);
}

void GraphDrawer::drawDetailedDifficulties(int edgeId,Edge * edge) {
    if (edge->getDifficulty() == 1) graphViewer->setEdgeColor(edgeId, GREEN);
    else if (edge->getDifficulty() == 2) graphViewer->setEdgeColor(edgeId, YELLOW);
    else if (edge->getDifficulty() == 3) graphViewer->setEdgeColor(edgeId, CYAN);
    else if (edge->getDifficulty() == 4) graphViewer->setEdgeColor(edgeId, BLUE);
    else if (edge->getDifficulty() == 5) graphViewer->setEdgeColor(edgeId, PINK);
    else if (edge->getDifficulty() == 6) graphViewer->setEdgeColor(edgeId, ORANGE);
    else if (edge->getDifficulty() == 7) graphViewer->setEdgeColor(edgeId, MAGENTA);
    else if (edge->getDifficulty() == 8) graphViewer->setEdgeColor(edgeId, RED);
    else if (edge->getDifficulty() == 9) graphViewer->setEdgeColor(edgeId, GRAY);
    else graphViewer->setEdgeColor(edgeId, BLACK);
}

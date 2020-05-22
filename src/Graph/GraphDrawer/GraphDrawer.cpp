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

        string color;
        if(node.second->getTags().size() != 0) {
            color = parseColor(node.second->getTags()[0]);
            graphViewer->setVertexColor(node.second->getId(), color);
            if (color == ORANGE) graphViewer->setVertexSize(node.second->getId(), 10);
        }
        if (color != ORANGE) graphViewer->setVertexSize(node.second->getId(), 0.1);
    }
    for(auto v: graph->pointsToDraw){
        if(v.size()) {
            graphViewer->setVertexColor(v[0](), RED);
            graphViewer->setVertexSize(v[0](), 20);
            graphViewer->setVertexColor(v.back()(), BLUE);
            graphViewer->setVertexSize(v.back()(), 20);
        }
    }
    graphViewer->setVertexColor(graph->pointsToDraw[0].back()(), GREEN);
}

void GraphDrawer::drawEdges(Graph *graph,int &cont) {
    cout << "\tDrawing Edges...\n";

    for(pair<long,Node *> node : graph->getNodes()) {
        for (Edge *edge :node.second->getEdges()) {
            graphViewer->addEdge(cont, node.first, edge->getDestination()->getId(), EdgeType::UNDIRECTED);
            //drawDifficulties(cont,edge);
            cont++;
        }
    }
}

void GraphDrawer::drawPath(Graph *graph, int &cont) {

    cout << "\tDrawing Path...\n" ;
    int size = graph->pointsToDraw.size();
    if(size == 0) return;
    int lastVectorSize = graph->pointsToDraw[size-1].size();

    for(int it=graph->pointsToDraw.size()-1;it>= 0;it--){
        for (int j = graph->pointsToDraw[it].size()-1; j > 0 ; --j) {
            Node orig = graph->pointsToDraw[it][j];
            Node dest = graph->pointsToDraw[it][j -1];
            graphViewer->addEdge(cont,orig.getId(),dest.getId(),EdgeType::DIRECTED);
            //Beautiful LGBT for A*
            if(graph->getNumOfConfluencePoints() == 0 && graph->getSelectedDiff().size() == 1){
                graphViewer->setEdgeThickness(cont, graph->getSelectedDiff()[it/(graph->getNumOfConfluencePoints()-1)]*3);
                drawDetailedDifficulties(cont,graph->findEdge(orig, dest));
            }else{ //Lame design with one color per group
                graphViewer->setEdgeColor(cont, getColor(graph->getSelectedDiff()[it/(graph->getNumOfConfluencePoints()-1)]));
                drawDetailedThicknesses(cont, graph->findEdge(orig, dest));
            }
            cont++;
        }
    }
}

string GraphDrawer::parseColor(string tag){
    string tagType;
    std::string::size_type pos = tag.find('=');
    if (pos != std::string::npos) tagType = tag.substr(0, pos);
    if(tagType == "tourism") return ORANGE;
    return YELLOW;

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

void GraphDrawer::drawDetailedThicknesses(int edgeId, Edge *edge) {
    if (edge->getDifficulty() == 1) graphViewer->setEdgeThickness(edgeId, 1);
    else if (edge->getDifficulty() == 2) graphViewer->setEdgeThickness(edgeId, 2);
    else if (edge->getDifficulty() == 3) graphViewer->setEdgeThickness(edgeId, 3);
    else if (edge->getDifficulty() == 4) graphViewer->setEdgeThickness(edgeId, 4);
    else if (edge->getDifficulty() == 5) graphViewer->setEdgeThickness(edgeId, 5);
    else if (edge->getDifficulty() == 6) graphViewer->setEdgeThickness(edgeId, 6);
    else if (edge->getDifficulty() == 7) graphViewer->setEdgeThickness(edgeId, 7);
    else if (edge->getDifficulty() == 8) graphViewer->setEdgeThickness(edgeId, 8);
    else if (edge->getDifficulty() == 9) graphViewer->setEdgeThickness(edgeId, 9);
    else graphViewer->setEdgeThickness(edgeId, 10);
}

string GraphDrawer::getColor(int diff){
    if (diff == 1) return GREEN;
    if (diff == 2) return YELLOW;
    if (diff == 3) return CYAN;
    if (diff == 4) return BLUE;
    if (diff == 5) return PINK;
    if (diff == 6) return ORANGE;
    if (diff == 7) return MAGENTA;
    if (diff == 8) return RED;
    if (diff == 9) return GRAY;
    return BLACK;
}


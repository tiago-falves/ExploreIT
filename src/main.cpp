
#include "iostream"
#include "Graph.h"
#include "Graph/GraphDrawer/GraphDrawer.h"
#include "Graph/GraphLoader/GraphLoader.h"


int main()
{
    Graph * graph = new Graph();
    GraphDrawer * drawer = new GraphDrawer(2000,2000);
    GraphLoader::loadGraph(graph);
    //cout <<to_string(zas->getX());
    int origin=150;
    int dest=151;
    graph->Dijkstra(origin,dest,250);
    graph->pointsToDraw = graph->getPath(origin,dest);
    drawer->drawFromGraph(graph);
}


#include "iostream"
#include "Graph/graph.h"
#include "Graph/GraphDrawer/GraphDrawer.h"
#include "Graph/GraphLoader/GraphLoader.h"


int main()
{
    Graph * graph = new Graph();
    GraphDrawer * drawer = new GraphDrawer(2000,2000);
    GraphLoader::loadGraph(graph);
    //cout <<to_string(zas->getX());

    graph->Dijkstra();
    drawer->drawFromGraph(graph);
}

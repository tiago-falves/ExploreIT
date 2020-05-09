
#include "iostream"
#include "Graph/graph.h"
#include "Graph/GraphDrawer/GraphDrawer.h"
#include "Graph/GraphLoader/GraphLoader.h"


int main()
{
    Graph * graph = new Graph();
    GraphDrawer * drawer = new GraphDrawer(2000,2000);
    GraphLoader::loadGraph(graph);
    //drawer->drawFromGraph(graph);
    //Node * zas = a->findNode(26018671);
    //cout <<to_string(zas->getX());

    graph->Dijkstra();
}

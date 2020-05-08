#include <src/Utils/GraphLoader.h>
#include "iostream"
#include "src/Graph/graph.h"

int main()
{
    Graph * a = new Graph();
    GraphLoader::loadGraph(a);
    //a.Dijkstra();
}

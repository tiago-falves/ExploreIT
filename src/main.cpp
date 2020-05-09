
#include <GraphLoader/GraphLoader.h>
#include <chrono>
#include "iostream"
#include "Graph/graph.h"
#include "Graph/GraphDrawer/GraphDrawer.h"


int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    Graph<Node> * graph = new Graph<Node>();
    GraphDrawer * drawer = new GraphDrawer(2000,2000);
    GraphLoader::loadGraph(graph);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    cout<<elapsed.count()<<endl;

    start = std::chrono::high_resolution_clock::now();
    graph->dijkstraShortestPath(Node(40,0,0),Node(200,0,0));
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    cout<<elapsed.count()<<endl;

    drawer->drawFromGraph(graph);
}

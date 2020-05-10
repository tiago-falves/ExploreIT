
#include "iostream"
#include "Graph.h"
#include "Graph/GraphDrawer/GraphDrawer.h"
#include "Graph/GraphLoader/GraphLoader.h"
#include <chrono>


int main()
{
    Graph * graph = new Graph();
    GraphDrawer * drawer = new GraphDrawer(2000,2000);
    int origin=150;
    int dest=151;
    
    //load
    auto start = std::chrono::high_resolution_clock::now();
    GraphLoader::loadGraph(graph);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Load time: " << elapsed.count() << " s\n"<<endl;

    //floyd
    start = std::chrono::high_resolution_clock::now();
    graph->FloydWarshall();
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "Floyd time: " << elapsed.count() << " s\n"<<endl;

    //dikstra
    start = std::chrono::high_resolution_clock::now();
    graph->Dijkstra(origin,dest,250);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "Dijkstra time: " << elapsed.count() << " s\n"<<endl;

    //drawer
    start = std::chrono::high_resolution_clock::now();
    graph->pointsToDraw = graph->getPath(origin,dest);
    drawer->drawFromGraph(graph);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "Drawer time: " << elapsed.count() << " s\n"<<endl;

}

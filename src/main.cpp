
#include "iostream"
#include "Graph.h"
#include "Graph/GraphDrawer/GraphDrawer.h"
#include "Graph/GraphLoader/GraphLoader.h"
#include <chrono>

bool IS_TESTING = false;

void dijkstra(Graph * graph,int origin,int dest){
    //dikstra
    auto start = std::chrono::high_resolution_clock::now();
    int distance;
    if(IS_TESTING) distance = 10;
    else distance = 1000;
    graph->Dijkstra(origin, dest, distance);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Dijkstra time: " << elapsed.count() << " s\n" << endl;
}

void loadGraph(Graph * graph){
    //load
    auto start = std::chrono::high_resolution_clock::now();
    GraphLoader::loadGraph(graph,IS_TESTING);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Load time: " << elapsed.count() << " s\n" << endl;
}

void drawer(Graph * graph,int origin,int dest){
    GraphDrawer *drawer = new GraphDrawer(2000, 2000);
    auto start = std::chrono::high_resolution_clock::now();
    graph->pointsToDraw = graph->getPath(origin, dest);
    drawer->drawFromGraph(graph);

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Drawer time: " << elapsed.count() << " s\n" << endl;
}

void floydWarshall(Graph * graph){
    auto start = std::chrono::high_resolution_clock::now();
    graph->FloydWarshall();
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Floyd time: " << elapsed.count() << " s\n" << endl;
}

void cleanGraphRuntime(Graph * graph,int origin){
    cout << "Comecado DFS\n";

    graph->DFSConnectivity(origin);
    cout << "Acabado DFS\n";
    graph->removeUnvisited(graph);
    cout << "Removidos DFS\n";

}



int main() {

    int origin,dest;
    Graph *graph = new Graph();


    if(!IS_TESTING){
        origin = 1330250426;
        dest = 1330250483;
    } else{
        origin = 12;
        dest = 22;
    }

    loadGraph(graph);
    cleanGraphRuntime(graph,origin);
    dijkstra(graph,origin,dest);
    drawer(graph,origin, dest);

}




#include "iostream"
#include "Graph.h"
#include "Graph/GraphDrawer/GraphDrawer.h"
#include "Graph/GraphLoader/GraphLoader.h"
#include <chrono>
#include <climits>

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

    graph->DFSConnectivity(origin);
    graph->removeUnvisited(graph);
}

void calculateMinMax(Graph* graph){

    graph->min_x = INT_MAX;
    graph->min_y = INT_MAX;
    graph->max_x = 0;
    graph->max_y = 0;



    std::unordered_map<long, Node*>::iterator it = graph->getNodes().begin();
    while(it != graph->getNodes().end()){
        int x = it->second->getX();
        int y = it->second->getY();
        if(x > graph->max_x)  graph->max_x = x;
        if(x < graph->min_x)  graph->min_x = x;
        if(y > graph->max_y)  graph->max_y=y;
        if(y < graph->min_y)  graph->min_y=y;
    }

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

    //floydWarshall(graph);
}



//
// Created by tiago on 17/05/2020.
//


#include "Menu.h"
#include <stdio.h>
#include <iostream>
#include "Graph.h"
#include "Graph/GraphDrawer/GraphDrawer.h"
#include "Graph/GraphLoader/GraphLoader.h"
#include <chrono>
#include <climits>
#include <Graph/Preprocessor.h>
#include <thread>

using namespace std;

Menu::Menu(Graph * graph) : graph(graph) {


}

void Menu::runMapMenu(){

    int option;
    int origin,dest;

    while(true) {
        menuSeparator();

        cout << "Welcome to ExploreIT! Which city do you want to hike?" << endl << endl;
        cout << "Please choose what is your option:" << endl << endl;
        cout << "Exit                                                               [0]" << endl;
        cout << "Aveiro                                                             [1]" << endl;
        cout << "Braga                                                              [2]" << endl;
        cout << "Coimbra                                                            [3]" << endl;
        cout << "Ermesinde                                                          [4]" << endl;
        cout << "Fafe                                                               [5]" << endl;
        cout << "Gondomar                                                           [6]" << endl;
        cout << "Lisboa                                                             [7]" << endl;
        cout << "Maia                                                               [8]" << endl;
        cout << "Porto                                                              [9]" << endl;
        cout << "Viseu                                                              [10]" << endl;
        cout << "Portugal                                                           [11]" << endl;
        cout << "GridGraphs 4*4                                                     [12]" << endl;
        cout << "GridGraphs 8*8                                                     [13]" << endl;
        cout << "GridGraphs 16*16                                                   [14]" << endl << endl;
        cout << "Insert the number correspondent to your option: ";
        cin >> option;
        validOption(option, 15);

        menuSeparator();

        if(option >= 12) IS_TESTING = true;
        initialVertices(origin,dest,option);

        runMenu(origin,dest);
    }
}

void Menu::setFolder(string graphDirectory){
    if(!IS_TESTING){
        nodeFileName = "nodes_x_y_";
        edgesFileName = "edges_";
        nodeFileName += graphDirectory + ".txt";
        edgesFileName += graphDirectory + ".txt";
        connectivityFileName = "connectivity.txt";

        string temp = graphDirectory;
        temp[0] = toupper(temp[0]);
        directory = "../data/PortugalMaps/" + temp + "/";
        tagFilePath = "../data/TagExamples/" + temp + "/t03_tags_" + graphDirectory + ".txt";

    }else{
        directory = "../data/GridGraphs/" + graphDirectory + "/";
        nodeFileName = "nodes.txt";
        edgesFileName = "edges.txt";
    }

}



//Runs the main Menu
void Menu::runMenu(int origin, int dest) {
    int option;

    loadGraph();
    if(IS_FIRST_TIME) preprocess(directory);
    getOriginDest(origin, dest);



    while(true) {


        menuSeparator();
        cout << endl << "Please choose what is your option:" << endl << endl;

        cout << "Exit                                                               [0]" << endl;
        cout << "Draw Graph                                                         [1]" << endl;
        cout << "Preprocess                                                         [2]" << endl;
        cout << "DFS Connectivity                                                   [3]" << endl;
        cout << "A* between 2 points                                                [4]" << endl;
        cout << "Floyd Warshall                                                     [5]" << endl;
        cout << "AStar Threads                                                      [6]" << endl << endl;
        cout << "Insert the number correspondent to your option: ";
        cin >> option;
        validOption(option, 6);

        menuSeparator();

        if (option == 0) { exit(0); }
        else if (option == 1) { drawer(origin,dest);  }
        else if (option == 2) { preprocess(directory); }
        else if (option == 3) { cleanGraphRuntime(origin,dest); }
        else if (option == 4) { AStar(origin,dest); }
        else if (option == 5) { floydWarshall(graph); }
        else if (option == 6) { AStarThreads(origin,dest); }
    }
}



void calculateHeights(Graph *pGraph);

void drawerS(int origin,int dest,Graph *graph){
    GraphDrawer *drawer = new GraphDrawer(2000, 2000);
    auto start = std::chrono::high_resolution_clock::now();
    drawer->drawFromGraph(graph);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Drawer time: " << elapsed.count() << " s\n" << endl;
}

void Menu::drawer(int origin,int dest){
    GraphDrawer *drawer = new GraphDrawer(2000, 2000);
    auto start = std::chrono::high_resolution_clock::now();
    graph->pointsToDraw = graph->getPath(origin, dest);
    drawer->drawFromGraph(graph);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Drawer time: " << elapsed.count() << " s\n" << endl;
}

void Menu::AStar(int origin, int dest){
    //AStar
    //cleanGraphRuntime(origin, dest);
    vector<vector<Node>> vectors;
    auto start = std::chrono::high_resolution_clock::now();
    int distance;
    if(IS_TESTING) distance = 20;
    else distance = 5479;
    graph->AStar(origin, dest, distance, 3);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "A* time: " << elapsed.count() << " s\n" << endl;
    drawer(origin,dest);

}

void Menu::AStarThreads(int origin, int dest){
    //AStar
    //cleanGraphRuntime(origin, dest);
    vector<vector<Node>> vectors;
    auto start = std::chrono::high_resolution_clock::now();
    int distance;
    if(IS_TESTING) distance = 5479;
    else distance = 5479;
    graph->AStar(origin, dest, distance, 3);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "A* time: " << elapsed.count() << " s\n" << endl;
    graph->pointsToDraw = graph->getPath(origin, dest);
    vectors.push_back(graph->pointsToDraw);

    if(IS_TESTING) distance = 5479;
    else distance = 5479;
    graph->AStar(origin, dest, distance, 5);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "A* time: " << elapsed.count() << " s\n" << endl;
    graph->pointsToDraw = graph->getPath(origin, dest);
    vectors.push_back(graph->pointsToDraw);

    if(IS_TESTING) distance = 5479;
    else distance = 5479;
    graph->AStar(origin, dest, distance, 10);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "A* time: " << elapsed.count() << " s\n" << endl;
    graph->pointsToDraw = graph->getPath(origin, dest);
    vectors.push_back(graph->pointsToDraw);

    float diff1=0;
    for(auto i:vectors.at(0)){
        if(std::find(vectors.at(1).begin(), vectors.at(1).end(), i) == vectors.at(1).end()) {
            diff1++;
        }
    }
    diff1/=vectors.at(0).size();


    float diff2=0;
    for(auto i:vectors.at(0)){
        if(std::find(vectors.at(2).begin(), vectors.at(2).end(), i) == vectors.at(2).end()) {
            diff2++;
        }
    }
    diff2/=vectors.at(0).size();


    float diff3=0;
    for(auto i:vectors.at(2)){
        if(std::find(vectors.at(1).begin(), vectors.at(1).end(), i) == vectors.at(1).end()) {
            diff3++;
        }
    }
    diff3/=vectors.at(2).size();

    cout<< "Diferença 0 1: "<<diff1 << endl;
    cout<< "Diferença 0 2: "<<diff2 << endl;
    cout<< "Diferença 1 2: "<<diff3 << endl;
    drawer(origin,dest);
}

void Menu::floydWarshall(Graph * graph){
    auto start = std::chrono::high_resolution_clock::now();
    graph->FloydWarshall(directory);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Floyd time: " << elapsed.count() << " s\n" << endl;
}

void Menu::cleanGraphRuntime(int origin,int dest){
    graph->DFSConnectivity(origin);
    cout << "Size " << graph->getNodes().size() << endl;
    graph->removeUnvisited(graph);
    cout << "Size " << graph->getNodes().size() << endl;
    drawer(origin,dest);
}



void Menu::preprocess(string directory) {

    Preprocessor preprocessor = Preprocessor(graph);
    preprocessor.preProcessDifficulties();
    preprocessor.saveDifficulties(directory);
    //if (IS_TESTING) preprocessor.setGridPOIs(gridNum);
    //preprocessor.preprocessConnectivity(directory);
}



//Outputs a separator made of *
void Menu::menuSeparator() {
    cout << endl << endl;
    for (int i = 0; i < 70; i++) { cout << "="; }
    cout << endl;
}

void Menu::validOption(int &option,int optionsNumber){
    while (cin.fail() || option < 0 || option > optionsNumber)
    {
        cout << "Invalid option, please insert the option again: ";
        cin.clear();
        cin.ignore(100, '\n');
        cin >> option;
    }
    cin.clear();
    cin.ignore(100, '\n');
}

void Menu::loadGraph(){
    cout << "Loading Graph...\n";
    GraphLoader loader = GraphLoader(graph,directory,nodeFileName,edgesFileName,tagFilePath);
    auto start = std::chrono::high_resolution_clock::now();
    loader.loadGraph(IS_TESTING);
    loader.setConnectivityFile(directory+connectivityFileName);
    //loader.loadConnectivity();
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Load time: " << elapsed.count() << " s\n" << endl;
}

const string &Menu::getTagFilePath() const {
    return tagFilePath;
}

void Menu::setTagFilePath(const string &tagFilePath) {
    Menu::tagFilePath = tagFilePath;
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

void Menu::getOriginDest(int &origin,int &dest){
    //Getting origin and dest
    if(!graph->getGraphs().empty()){
        int index = graph->getMostConnected();
        origin = graph->getGraphsVector().at(index).at(0);
        dest = graph->getGraphsVector().at(index).at(1);
    }
}

void Menu::initialVertices(int &origin,int &dest,int option){
    if (option == 0) { exit(0); }
    else if (option == 1) {
        //Aveiro
        origin = 26019978;
        dest = 26019992;
        setFolder("aveiro");
    }
    else if (option == 2) {
        //Braga
        origin = 450543314;
        dest = 450543328;
        setFolder("braga");
    }
    else if (option == 3) {
        //Coimbra
        origin = 206155873;
        dest = 206155874;
        setFolder("coimbra");

    }
    else if (option == 4) {
        //Ermesinde
        origin = 25449700;
        dest = 25449701;
        setFolder("ermesinde");
    }
    else if (option == 5) {
        //Fafe
        origin = 26130479;
        dest = 26130480;
        setFolder("fafe");
    }
    else if (option == 6) {
        //Gondomar
        origin = 112624356;
        dest = 112624357;
        setFolder("gondomar");
    }
    else if (option == 7) {
        //Lisboa
        origin = 582518621;
        dest = 582518622;
        setFolder("lisboa");
    }
    else if (option == 8) {
        //Maia
        origin = 26058104;
        dest = 26058105;
        setFolder("maia");
    }
    else if (option == 9) {
        //Porto
        origin = 90379613;
        dest = 90379614;
        setFolder("porto");
    }
    else if (option == 10) {
        //Viseu
        origin = 26023650;
        dest = 26023652;
        setFolder("viseu");
    }
    else if (option == 11) {
        //Portugal
        origin = 158862065;
        dest = 158862066;
        setFolder("portugal");
    }
    else if (option == 12) {
        //4*4
        origin = 0;
        dest = 2;
        setFolder("4x4");
        gridNum = 4;
    }
    else if (option == 13) {
        //8x8
        origin = 0;
        dest = 2;
        setFolder("8x8");
        gridNum = 8;
    }
    else if (option == 14) {
        //16x16
        origin = 0;
        dest = 2;
        setFolder("16x16");
        gridNum = 16;
    }

}
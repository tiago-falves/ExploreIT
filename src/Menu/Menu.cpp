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
    this->preprocessor = new Preprocessor(graph);
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
        cout << "Porto Old                                                          [9]" << endl;
        cout << "Porto Full                                                         [10]" << endl;
        cout << "Penafiel                                                           [11]" << endl;
        cout << "Espinho                                                            [12]" << endl;
        cout << "Viseu                                                              [13]" << endl;
        cout << "Portugal                                                           [14]" << endl;
        cout << "GridGraphs 4*4                                                     [15]" << endl;
        cout << "GridGraphs 8*8                                                     [16]" << endl;
        cout << "GridGraphs 16*16                                                   [17]" << endl;
        cout << "GridGraphs 100*100                                                 [18]" << endl << endl;
        cout << "Insert the number correspondent to your option: ";
        cin >> option;
        validOption(option, 18);

        menuSeparator();

        if(option >= 15) IS_TESTING = true;
        else IS_TESTING = false;

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
        floydFileName = "floydWarshallOutput.txt";
        string temp = graphDirectory;
        temp[0] = toupper(temp[0]);
        directory = "../data/PortugalMaps/" + temp + "/";
        tagFilePath = "../data/TagExamples/" + temp + "/t03_tags_" + graphDirectory + ".txt";
    }else{
        directory = "../data/GridGraphs/" + graphDirectory + "/";
        nodeFileName = "nodes.txt";
        edgesFileName = "edges.txt";
        connectivityFileName = "connectivity.txt";
        floydFileName = "floydWarshallOutput.txt";

    }
}



//Runs the main Menu
void Menu::runMenu(int origin, int dest) {
    int option;

    loadGraph();
    getOriginDest(origin, dest);

    while(true) {


        menuSeparator();

        cout << endl << "Please choose what is your option:" << endl << endl;

        cout << "Exit                                                               [0]" << endl;
        cout << "Draw Graph                                                         [1]" << endl;
        cout << "Preprocess                                                         [2]" << endl;
        cout << "DFS Connectivity                                                   [3]" << endl;
        cout << "Best path considering distance                                     [4]" << endl;
        cout << "Best path with distance and difficulty                             [5]" << endl;
        cout << "A* between 2 points                                                [6]" << endl;
        cout << "Floyd Warshall                                                     [7]" << endl;
        cout << "Algorithm with many confluence points                              [8]" << endl;
        cout << "Default algorithm for map                                          [9]" << endl;
        cout << "Mandatory Points                                                   [10]" << endl << endl;
        cout << "Insert the number correspondent to your option: ";
        cin >> option;
        validOption(option, 10);

        menuSeparator();

        if (option == 0) { exit(0); }
        else if (option == 1) { drawer(origin,dest);  }
        else if (option == 2) { preprocess(directory); }
        else if (option == 3) { showBiggestConnectedGraph(origin,dest); }
        else if (option == 4) { AStar(origin,dest,"distance"); }
        else if (option == 5) { AStar(origin,dest,"diff"); }
        else if (option == 6) { AStar(origin,dest); }
        else if (option == 7) { floydWarshall(graph); }
        else if (option == 8) { runMasterpiece(); }
        else if (option == 9) { defaultRun(directory); }
        else if (option == 10){ MandatoryPoints(); }
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

    cout <<"Number Edges: " << graph->getEdges().size() << "\nNodes: " << graph->getNodes().size() << endl;
    GraphDrawer *drawer = new GraphDrawer(2000, 2000);
    auto start = std::chrono::high_resolution_clock::now();
    //graph->pointsToDraw = graph->getPath(origin, dest);
    drawer->drawFromGraph(graph);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Drawer time: " << elapsed.count() << " s\n" << endl;
}





void Menu::drawer(vector<int> confluencePoints){

    GraphDrawer *drawer = new GraphDrawer(2000, 2000);
    auto start = std::chrono::high_resolution_clock::now();
    drawer->drawFromGraph(graph);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Drawer time: " << elapsed.count() << " s\n" << endl;

}


void Menu::AStar(int origin, int dest,string option){
    //AStar
    vector<int> difficulties;
    int diff = 6;
    difficulties.push_back(diff);
    cleanGraphRuntime(origin, dest);
    vector<vector<Node>> vectors;
    int distance;
    distance = 20;
    graph->setSelectedDiff(difficulties);
    graph->AStar(origin, dest, distance , diff, nullptr,option);
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
    cout << "Initial Size: " << graph->getNodes().size() << endl;
    graph->removeUnvisited(graph);
    cout << "Connected Graph Size: " << graph->getNodes().size() << endl;
}



void Menu::preprocess(string directory) {
    preprocessor->preProcessDifficulties();
    preprocessor->saveDifficulties(directory);
    //preprocessor->setGridPOIs(gridNum);
    preprocessor->preprocessConnectivity(directory);
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

    GraphLoader loader = GraphLoader(graph,directory,nodeFileName,edgesFileName,tagFilePath,floydFileName);
    auto start = std::chrono::high_resolution_clock::now();
    loader.loadGraph(IS_TESTING);
    loader.setConnectivityFile(directory+connectivityFileName);
    loader.loadConnectivity();
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
        int RandIndex = rand() % graph->getGraphsVector().at(index).size();
        int RandIndex2 = rand() % graph->getGraphsVector().at(index).size();
        origin = graph->getGraphsVector().at(index).at(RandIndex);
        dest = graph->getGraphsVector().at(index).at(RandIndex2);
    }
}

void Menu::initialVertices(int &origin,int &dest,int option){
    if(!IS_TESTING) distanceEdges = 100; //Varios blocos de 100 metros
    if (option == 0)  exit(0);
    else if (option == 1)    setFolder("aveiro");
    else if (option == 2) setFolder("braga");
    else if (option == 3) setFolder("coimbra");
    else if (option == 4) setFolder("ermesinde");
    else if (option == 5) setFolder("fafe");
    else if (option == 6) setFolder("gondomar");
    else if (option == 7) setFolder("lisboa");
    else if (option == 8) setFolder("maia");
    else if (option == 9) setFolder("porto");
    else if (option == 10) setFolder("porto_full");
    else if (option == 11) setFolder("penafiel");
    else if (option == 12) setFolder("espinho");
    else if (option == 13) setFolder("viseu");
    else if (option == 14) setFolder("portugal");
    else if (option == 15) {
        //4*4
        distanceEdges = 150;
        setFolder("4x4");
        gridNum = 4;
    }
    else if (option == 16) {
        //8x8
        distanceEdges = 75;
        setFolder("8x8");
        gridNum = 8;
    }
    else if (option == 17) {
        //16x16
        distanceEdges = 37;
        setFolder("16x16");
        gridNum = 16;
    }
    else if (option == 18) {
        //100*100
        distanceEdges = 1;
        setFolder("100x100");
        gridNum = 100;
    }
}

//Add default points
void Menu::runMasterpiece(){
    int size = askForInt("How much confluence Points? ");
    graph->setNumOfConfluencePoints(size);
    vector<int> confluenceNodeIds;
    vector<int> times;
    vector<int> difficulties;

    //First Node
    int nodeId = askForId();
    int confluenceHour = askForInt("Hour of confluence (Para ja e so distancia acumulada)");
    confluenceNodeIds.push_back(nodeId);
    times.push_back(confluenceHour);

    int connectedGraph = graph->getNodeConnectedGraph(nodeId);
    if(connectedGraph == -1){
        cout << "Error getting connected Graph of the point\n";
        return;
    }

    for (int i = 1; i < size; ++i) {
        int nodeId = askForId();
        if(!graph->isInConnectedGraph(connectedGraph,nodeId)){
            cout << "Error, that point does not belong to same connected Graph\n";
            return;
        }
        int confluenceHour = askForInt("Hour of confluence (Para ja e so distancia acumulada)") * distanceEdges;
        confluenceNodeIds.push_back(nodeId);
        times.push_back(confluenceHour);


    }
    int difficultyNumber = askForInt("How many groups? ");
    for (int j = 0; j < difficultyNumber; ++j) {
        int difficulty = askForInt("Please insert difficulty: ");
        validDifficulty(difficulty);
        difficulties.push_back(difficulty);
    }

    graph->setSelectedDiff(difficulties);
    graph->calculateInterestingPath(confluenceNodeIds,times,difficulties,0);

    drawer(confluenceNodeIds);
}



vector<string> Menu::askForStringVectorAll(string what){
    cout << "Please Insert the " << what << ", click enter to exit" << endl;
    vector<string> things;
    while (true){
        string x =askForString(what);
        if(x == "") break;
        things.push_back(x);
    }
    return things;
}
//Trim
void trimRight(string &s) {
    s.erase(s.find_last_not_of(" ") + 1);
}
void trimLeft(string &s) {
    s.erase(0, s.find_first_not_of(" "));
}
void trim(string &s) {
    trimRight(s);
    trimLeft(s);
}
void validInt(string num) {
    try {stoi(num);}
    catch (std::invalid_argument ia){ throw;}
}

//Asks the user to insert a string of type what
string Menu::askForString(const string &what){
    string name;
    cout << what << ": ";
    getline(cin,name);
    trimLeft(name);
    return name;
}

bool Menu::askForBool(string text){
    string name = askForString(text);

    if(name == "Y" || name == "Yes" || name == "T" || name == "True" || name == "yes" || name == "y"){
        return true;
    }
    else if(name == "N" || name == "No" || name == "F" || name == "False" || name == "no" || name == "n"){
        return false;
    }
    else{
        cout << "Please insert a valid input. The options are: True, Yes, T, Y, False, No, N, F.\n";
        return askForBool(text);
    }
}

int Menu::askForId(){
    int id;
    cout << "Please Insert Node ID: ";
    cin >> id;
    validCin(id);
    cin.clear();
    cin.ignore(100, '\n');
    return id;
}

//Asks for a valid int until the user inputs it
void Menu::validCin(int &option) {
    while (cin.fail())
    {
        cout << "Invalid input, please insert your answer again: ";
        cin.clear();
        cin.ignore(100, '\n');
        cin >> option;
    }
}

int Menu::askForInt(const string &what) {
    bool exceptionCatched = true;
    string text;
    cout << what << ": ";
    cin >> text;

    while(exceptionCatched) {
        try {
            validInt(text);
            exceptionCatched = false;
        }
        catch (std::invalid_argument ia) {
            cout << "Invalid number, please insert your answer again: ";
            cin.clear();
            cin.ignore(100, '\n');
            cin >> text;
        }

    }
    cin.clear();
    cin.ignore(100, '\n');
    return stoi(text);
}

void Menu::validDifficulty(int &option){
    while (cin.fail() || option < 0 || option > 10)
    {
        cout << "Invalid Difficulty, please insert again: ";
        cin >> option;
        cin.clear();
        cin.ignore(100, '\n');
    }
}

void Menu::showBiggestConnectedGraph(int origin, int dest){
    cleanGraphRuntime(origin,dest);
    drawer(origin,dest);
}

void Menu::defaultRun(string directory) {
    vector<int> confluenceNodeIds; int id;
    vector<int> times; int time;
    vector<int> difficulties; int diff;
    char point;

    ifstream def; def.open(directory + "default.txt");
    if (!def.is_open()){
        cout << "default.txt not found in " << directory << endl;
        return;
    }

    def >> id >> time;
    confluenceNodeIds.push_back(id);
    times.push_back(time);
    while (def >> id >> time){
        if (id == 0 && time == 0) break;
        confluenceNodeIds.push_back(id);
        times.push_back(time * distanceEdges) ;
        cout << id << " : " << time << endl;
    }
    cout << "Point: " << point << endl;
    while (def >> diff){
        cout << diff << endl;
        difficulties.push_back(diff);
    }

    def.close();

    graph->setNumOfConfluencePoints(confluenceNodeIds.size());
    graph->setSelectedDiff(difficulties);
    graph->calculateInterestingPath(confluenceNodeIds,times,difficulties,0);

    drawer(confluenceNodeIds);
}

void Menu::MandatoryPoints(){
    vector<int> a;
    a.push_back(0);
    a.push_back(50);
    a.push_back(60);

    vector<int> b;
    b.push_back(3);
    b.push_back(5);
    b.push_back(55);

    vector<int> c;
    c.push_back(0);
    c.push_back(70);
    c.push_back(100);

    vector<int> d;
    d.push_back(5);
    graph->mandatoryPOIS(a,b,c,d);
    drawer(d);
}


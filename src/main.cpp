
#include "iostream"
#include "Graph.h"
#include <Menu/Menu.h>

int main() {

    int origin,dest;
    Graph graph = Graph();

    Menu menu = Menu(&graph);
    menu.runMapMenu();

}





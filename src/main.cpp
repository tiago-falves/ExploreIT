
#include "Graph.h"
#include <Menu/Menu.h>

int main() {
    Graph graph = Graph();
    Menu menu = Menu(&graph);
    menu.runMapMenu();
}





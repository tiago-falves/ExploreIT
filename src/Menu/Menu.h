//
// Created by tiago on 17/05/2020.
//

#ifndef CAL1920_MENU_H
#define CAL1920_MENU_H


#include <Graph/Graph.h>

class Menu {


private:
    Graph * graph;
    bool IS_TESTING = false;
    bool IS_FIRST_TIME = true;
    string directory;
    string nodeFileName;
    string edgesFileName;
    string tagFilePath;
public:
    Menu(Graph * graph);

    void validOption(int &option, int optionsNumber);

    void menuSeparator();

    void runMenu(int origin,int destiny);

    void runMapMenu();

    void AStar(int origin, int dest);

    void loadGraph();

    void drawer(int origin, int dest);

    void preprocess(string directory);

    void cleanGraphRuntime(int origin,int dest);

    void setFolder(string city);

    const string &getTagFilePath() const;

    void setTagFilePath(const string &tagFilePath);
};


#endif //CAL1920_MENU_H

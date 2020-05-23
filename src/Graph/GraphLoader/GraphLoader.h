//
// Created by tiago on 08/05/2020.
//

#ifndef CAL1920_GRAPHLOADER_H
#define CAL1920_GRAPHLOADER_H

#include "Graph.h"


class GraphLoader {
public:


    GraphLoader(Graph * graph, const string &directory, const string &nodeFile, const string &edgeFile,const string &tagPath,const string &floydFileName);

    bool loadGraph(bool isGrid);

    bool loadDifficulties( );

    bool loadConnectivity();

    const string &getDirectory() const;

    void setDirectory(const string &directory);

    const string &getNodeFile() const;

    void setNodeFile(const string &nodeFile);

    const string &getEdgeFile() const;

    void setEdgeFile(const string &edgeFile);



private:
    string directory;
    string nodeFile;
    string edgeFile;
    string tagPath;
    string floydFile;
    string connectivityFile;
public:
    const string &getConnectivityFile() const;

    void setConnectivityFile(const string &connectivityFile);

private:
    Graph * graph;

    bool loadEdges();
    bool loadNodes();
    bool loadTags(bool isGrid);


    bool loadFloyd();
};


#endif //CAL1920_GRAPHLOADER_H

//
// Created by tiago on 08/05/2020.
//

#ifndef CAL1920_GRAPHLOADER_H
#define CAL1920_GRAPHLOADER_H

#include "Graph.h"


class GraphLoader {
private:
    string directory;
    string nodeFile;
    string edgeFile;
    string tagPath;
    string floydFile;
    string connectivityFile;

    Graph * graph;
    bool loadEdges();
    bool loadNodes();
    bool loadTags(bool isGrid);
    bool loadFloyd();

public:

    /**
     * Constructs loader class. Directory and file names where information is loaded from are given as parameters.
     * @param graph
     * @param directory
     * @param nodeFile
     * @param edgeFile
     * @param tagPath
     * @param floydFileName
     */
    GraphLoader(Graph * graph, const string &directory, const string &nodeFile, const string &edgeFile,const string &tagPath,const string &floydFileName);

    /**
     * Loads graph.
     * @param isGrid True if a grid graph is being loaded.
     * @return True if loading was completed successfully.
     */
    bool loadGraph(bool isGrid);

    /**
     * Loads processed difficulties.
     * @return True if loading was completed successfully.
     */
    bool loadDifficulties( );

    /**
     * Loads strongly connected graph previously processed.
     * @return True if loading was completed successfully.
     */
    bool loadConnectivity();

    /**
     * Loads points of interest generated previously for grid graphs.
     * @param isGrid True if a grid graph is being loaded.
     * @return True if loading was completed successfully.
     */
    bool loadGridPOIS(bool isGrid);

    /**
     * Sets the connectivity file from where information is loaded
     * @param connectivityFile File name.
     */
    void setConnectivityFile(const string &connectivityFile);

    const string &getDirectory() const;

    void setDirectory(const string &directory);

    const string &getNodeFile() const;

    void setNodeFile(const string &nodeFile);

    const string &getEdgeFile() const;

    void setEdgeFile(const string &edgeFile);

    const string &getConnectivityFile() const;
};


#endif //CAL1920_GRAPHLOADER_H

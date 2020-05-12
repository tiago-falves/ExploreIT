//
// Created by tiago on 08/05/2020.
//

#ifndef CAL1920_GRAPHLOADER_H
#define CAL1920_GRAPHLOADER_H

#include "Graph.h"


class GraphLoader {
public:
    static bool loadGraph(Graph *graph, bool isGrid);
    static bool loadDifficulties(Graph *graph, string directory);


private:
    static bool loadEdges(Graph *graph,bool isGrid);
    static bool loadNodes(Graph *graph,bool isGrid);
    static bool loadTags(Graph *graph,bool isGrid);

};


#endif //CAL1920_GRAPHLOADER_H

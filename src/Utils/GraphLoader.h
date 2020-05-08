//
// Created by tiago on 08/05/2020.
//

#ifndef CAL1920_GRAPHLOADER_H
#define CAL1920_GRAPHLOADER_H

#include "../Graph/graph.h"


class GraphLoader {
public:
    static bool loadGraph(Graph *graph);

private:
    static bool loadEdges(Graph *graph);
    static bool loadNodes(Graph *graph);

};


#endif //CAL1920_GRAPHLOADER_H

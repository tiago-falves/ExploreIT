//
// Created by tiago on 08/05/2020.
//

#ifndef CAL1920_GRAPHLOADER_H
#define CAL1920_GRAPHLOADER_H

#include <Node.h>
#include "../graph.h"


class GraphLoader {
public:
    static bool loadGraph(Graph<Node> *graph);

private:
    static bool loadEdges(Graph<Node> *graph);
    static bool loadNodes(Graph<Node> *graph);

};


#endif //CAL1920_GRAPHLOADER_H

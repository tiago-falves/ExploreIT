//
// Created by tiago on 08/05/2020.
//

#ifndef CAL1920_GRAPHDRAWER_H
#define CAL1920_GRAPHDRAWER_H

#include "graphviewer.h"


class GraphDrawer {
private:
    int width, height;
    GraphViewer * graphViewer;

    /**
     * Draws nodes. Those who are points of interest are represented in a different color and size
     * @param graph
     */
    void drawNodes(Graph * graph);

public:
    /**
     * Resets drawn graph
     */
    void resetGraphViewer();
    /**
     * Draws graph given has parameter
     * @param graph
     */
    void drawFromGraph(Graph *graph);
    /**
     * Constructs GraphDrawer class
     * @param width
     * @param height
     */
    GraphDrawer(int width, int height);

    /**
     * Parses color from tag. Orange for tourism tagged nodes, yellow for the rest.
     * @param tag
     * @return YELLOW or ORANGE GraphViewer macros depending on tag parameter.
     */
    string parseColor(string tag);

    /**
     * Groups difficulties in 3 differents groups giving a color for each of them.
     * @param edgeId
     * @param edge
     */
    void drawDifficulties(int edgeId, Edge *edge);

    /**
     * Sets one different color for each difficulty.
     * @param edgeId
     * @param edge
     */
    void drawDetailedDifficulties(int edgeId, Edge * edge);

    /**
     * Sets edge's thickness according to difficulty.
     * @param edgeId
     * @param edge
     */
    void drawDetailedThicknesses(int edgeId,Edge * edge);

    /**
     * Gets the color correspondent to level of difficulty given as parameter.
     * @param diff
     * @return
     */
    string getColor(int diff);

    /**
     * Draws all edges in black color.
     * @param graph
     * @param cont
     */
    void drawEdges(Graph *graph, int &cont);

    /**
     * Draws the resulting path of the algorithm's application
     */
    void drawPath(Graph *graph, int &cont);
};


#endif //CAL1920_GRAPHDRAWER_H

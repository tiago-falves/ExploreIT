//
// Created by tiago on 08/05/2020.
//
#pragma once

#ifndef CAL1920_EDGE_H
#define CAL1920_EDGE_H

class Node;

class Edge
{
private:
    double weight;
    Node * destination;
    Node * origin;
    int id;
    int difficulty;

public:

    /**
     * Constructs edge given origin and destination nodes.
     * @param id
     * @param origin
     * @param destiny
     * @param weight
     */
    Edge(int id,Node *origin, Node *destiny, double weight);

    /**
     * Constructs edge given only destination node.
     * @param id
     * @param weight
     * @param destination
     */
    Edge(int id,float weight,Node *destination);

    /**
     * Gets edge destination node.
     * @return
     */
    Node * getDestination();

    /**
     * Gets edge origin node.
     * @return
     */
    Node * getOrigin();
    double getWeight();
    int getDifficulty() const;
    void setDifficulty(int difficulty);
    int getId() const;
    void setId(int id);
};


#endif //CAL1920_EDGE_H

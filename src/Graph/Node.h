//
// Created by tiago on 08/05/2020.
//
#pragma once

#ifndef CAL1920_NODE_H
#define CAL1920_NODE_H

#include <list>
#include "Edge.h"


class Node {
private:
    long int id = 0;
    std::list<Edge *> edges;
    double x = 0, y = 0;
public:
    Node(long int id, double x, double y);

    Node();

    void addEdge(Node * origin,Node *destination);

    double getX() const;

    double getY() const;

    long getId() const;

    std::list<Edge *> getEdges();

    bool operator<(Node b) {return this->getId() > b.getId();}

    long operator()() {return id;}

};

#endif //CAL1920_NODE_H

//
// Created by tiago on 08/05/2020.
//
#pragma once

#ifndef CAL1920_EDGE_H
#define CAL1920_EDGE_H

class Node;

class Edge
{
    double distance;
    Node *destination;
public:
    Edge(float distance,Node *destination);
    Node *getNode();
    double getDistance();
};


#endif //CAL1920_EDGE_H

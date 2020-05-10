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
    double id;
public:
    Edge(Node *origin, Node *destiny, double weight);
    Edge(float weight,Node *destination);
    Node * getDestination();
    Node * getOrigin();
    double getWeight();
};


#endif //CAL1920_EDGE_H

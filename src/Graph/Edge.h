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

    Edge(int id,Node *origin, Node *destiny, double weight);
    Edge(int id,float weight,Node *destination);
    Node * getDestination();
    Node * getOrigin();
    double getWeight();
    int getDifficulty() const;
    void setDifficulty(int difficulty);
    int getId() const;
    void setId(int id);
};


#endif //CAL1920_EDGE_H

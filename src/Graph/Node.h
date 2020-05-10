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
    double dist=0;
    double weight=0;
    double dist_target=0;
public:
    Node(long int id, double x, double y);

    int queueIndex = 0;
    Node();

    Node *path;

    bool visited = false;

    void addEdge(Node * origin,Node *destination);

    double getX() const;

    double getY() const;

    long getId() const;

    std::list<Edge *> getEdges();
    long operator()() {return id;}

    double getDist(){
        return dist;
    }
    double getDistTarget(){
        return dist_target;
    }
    double getWeight(){
        return weight;
    }

    void setDist(double d){
        dist=d;
    }
    void setDistTarget(double d){
        dist_target=d;
    }
    void setWeight(double w){
        weight=w;
    }



};

#endif //CAL1920_NODE_H

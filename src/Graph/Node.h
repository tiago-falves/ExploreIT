//
// Created by tiago on 08/05/2020.
//
#pragma once

#ifndef CAL1920_NODE_H
#define CAL1920_NODE_H

#include <list>
#include <vector>
#include "Edge.h"
#include <string>
using namespace std;


class Node {
private:
    long int id = 0;
    std::list<Edge *> edges;
    vector<string> tags;
    double x = 0, y = 0;
    double dist=0;
    double weight=0;
    double dist_target=0;
public:
    int queueIndex = 0;
    Node *path;
    bool visited = false;

    Node(long int id, double x, double y);
    Node();

    double getX() const;
    double getY() const;
    long getId() const;

    std::list<Edge *> getEdges();
    vector<string> getTags();
    double getDist(){return dist;}
    double getDistTarget(){return dist_target;}
    double getWeight(){return weight;}

    void setDist(double d){dist=d;}
    void setDistTarget(double d){dist_target=d;}
    void setWeight(double w){weight=w;}

    void addTag(std::string tag);
    void addEdge(Node * origin,Node *destination);

    long operator()() {return id;}

};

#endif //CAL1920_NODE_H

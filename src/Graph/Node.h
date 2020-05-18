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
    std::vector<Edge *> edges;
    vector<string> tags;
    double x = 0, y = 0;
    double dist=0;
    double summedDifficulties=0;
    double weight=0;
    double dist_target=0;
    int height = 0;
    int floydPosition;

public:
    bool violated_difficulty= false;
    int queueIndex = 0;
    Node *path;
    bool visited = false;

    Node(long int id, double x, double y);
    Node();

    double getX() const;
    double getY() const;
    long getId() const;

    std::vector<Edge *> getEdges();
    vector<string> getTags();
    double getDist(){return dist;}
    double getDistTarget(){return dist_target;}
    double getWeight(){return weight;}
    double getSummedDifficulties(){ return summedDifficulties;}

    void setDist(double d){dist=d;}
    void setDistTarget(double d){dist_target=d;}
    void setWeight(double w){weight=w;}
    void setSummedDifficulties(double d){ summedDifficulties=d;}
    void addDifficulty(double d){ summedDifficulties+=d;}

    void addTag(std::string tag);
    Edge * addEdge(int edgeId,Node * origin,Node *destination,int damage);

    long operator()() {return id;}
    long operator==(Node a) {return a.getId()==id;}

    void removeEdge(int destiny);

    Edge *findEdge(int destiny);

    int setFloydPosition(int floydPosition) {this->floydPosition = floydPosition;}
    int getFloydPostion() {return floydPosition;}
};

#endif //CAL1920_NODE_H

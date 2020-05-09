#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "Node.h"

using namespace std;



bool operator <(Node &a,Node &b);
class Graph
{
    unordered_map<long,Node*> nodes;
    vector<Edge*> edges;
public:
    unordered_map<long,Node*> getNodes();
    vector<Edge*> getEdges();
    double Dijkstra();
    Node *findNode(const int &id) const;
    bool addNode(const int &id, int x, int y);
    bool addEdge(int origId, int destId);
};


struct setpHash
{
    int operator() (const Node *ap) const
    {
        return ap->getId();
    }

    bool operator() (const Node  *ap1, const Node  *ap2) const
    {
        if ( ap1->getX() != ap2->getX() )
            return false;

        if(ap1->getY() != ap2->getY())
            return false;
        else {
            return ap1->getId()==ap2->getId();
        }
    }
};

class ww{
public:
    ww(Node *a,double d)
        :second(d),first(a){}
    double second;
    Node *first;
};


bool operator <(ww a,ww b);

#endif // GRAPH_H

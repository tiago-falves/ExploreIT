#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;



class Node;
class Edge;


class Edge
{
    double distance;
    Node *destination;
public:
    Edge(double distance,Node *destination);
    Node *getNode();
    double getDistance();
};

class Node
{
private:
    long int id=0;
    list<Edge*> edges;
    double x=0,y=0;
public:
    Node(long int id,double x,double y);
    Node();
    void addEdge(Node *destination);
    double getX() const;
    double getY() const;
    long  getId()  const;
    list<Edge*> getEdges();
    bool operator <(Node b){
        return this->getId()>b.getId();
    }
    long operator ()(){
        return id;
    }

};


bool operator <(Node &a,Node &b);
class Graph
{
    unordered_map<long,Node*> nodes;
public:
    unordered_map<long,Node*> getNodes();
    Graph();
    double Dijkstra();
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

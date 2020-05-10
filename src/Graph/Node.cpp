//
// Created by tiago on 08/05/2020.
//

#include <cmath>
#include "Node.h"
using namespace std;

Node::Node(long int id,double x,double y)
        :id(id),x(x),y(y)
{}

Node::Node()
{}
void Node::addEdge(Node *origin,Node *destination){
    float distance=0;
    double dx=abs(x-destination->x);
    double dy=abs(y-destination->y);
    distance=sqrt(dx*dx+dy*dy);
    edges.push_back(new Edge(origin,destination,distance));
}
double Node::getX() const{
    return x;
}
double Node::getY() const{
    return y;
}
long Node::getId() const{
    return id;
}

bool operator ==(Node a,Node b){
    return a.getId()==b.getId();
}
list<Edge*> Node::getEdges(){
    return edges;
}



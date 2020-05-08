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
void Node::addEdge(Node *destination){
    float distance=0;
    double dx=(pow(x,2)-(pow(destination->x,2)),2);
    double dy=(pow(y,2)-pow(destination->y,2),2);
    distance=sqrt(pow(dx,2.0)+pow(dy,2.0));
    edges.push_back(new Edge(distance,destination));
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
bool operator <(Node &a, Node &b){
    return a.getId()<b.getId();
}
bool operator ==(Node a,Node b){
    return a.getId()==b.getId();
}
list<Edge*> Node::getEdges(){
    return edges;
}



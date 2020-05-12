//
// Created by tiago on 08/05/2020.
//

#include <cmath>
#include <string>
#include <algorithm>
#include "Node.h"
using namespace std;

Node::Node(long int id,double x,double y)
        :id(id),x(x),y(y)
{}

Node::Node()
{}
void Node::addEdge(int edgeId,Node *origin,Node *destination){
    float distance=0;
    double dx=abs(x-destination->x);
    double dy=abs(y-destination->y);
    distance=sqrt(dx*dx+dy*dy);
    edges.push_back(new Edge(edgeId,origin,destination,distance));
}

void Node::removeEdge(int destiny){
    for (int i = 0; i < edges.size(); ++i) {
        if(edges[i]->getDestination()->getId() == destiny){
            edges.erase(edges.begin() + i);
            break;
        }
    }
}

Edge * Node::findEdge(int destiny){
    for (int i = 0; i < edges.size(); ++i) {
        if(edges[i]->getDestination()->getId() == destiny){
            return edges[i];
        }
    }
}
void Node::addTag(string tag ){
    tags.push_back(tag);
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
vector<Edge*> Node::getEdges(){
    return edges;
}
vector<string> Node::getTags(){
    return tags;
}




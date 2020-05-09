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



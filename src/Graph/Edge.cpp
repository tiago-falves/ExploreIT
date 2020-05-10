//
// Created by tiago on 08/05/2020.
//

#include "Edge.h"
#include "Node.h"

Edge::Edge(Node * origin, Node * destiny, double weight){
    this->origin = origin;
    this->destination = destiny;
    this->weight = weight;
}

Edge::Edge(float weight,Node *destination)
        :weight(weight),destination(destination) {}

Node *Edge::getDestination(){
    return destination;
}
double Edge::getWeight(){
    return weight;
}

Node *Edge::getOrigin() {
    return origin;
}


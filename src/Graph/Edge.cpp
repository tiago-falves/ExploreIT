//
// Created by tiago on 08/05/2020.
//

#include "Edge.h"
#include "Node.h"

Edge::Edge(float distance,Node *destination)
        :distance(distance),destination(destination) {}
Node *Edge::getNode(){
    return destination;
}
double Edge::getDistance(){
    return distance;
}


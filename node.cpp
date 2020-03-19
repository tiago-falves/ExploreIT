#include "node.h"

Node::Node(double longitude,double latitude,double altitude,long unsigned id)
    :longitude(longitude),latitude(latitude),altitude(altitude),id(id)
{
}


double Node::getLongitude(){
    return longitude;
}

double Node::getLatitude(){
    return latitude;
}

double Node::getAltitude(){
    return  altitude;
}

unsigned long Node::getId(){
    return id;
}

bool operator <(Node &a,Node &b){
    return a.getId()<b.getId();
}

Node* Node::findNode(long unsigned id,vector<Node*> vector){
    int l=0;
    int r=vector.size()-1;
    int m=(r-l)/2;
    while (l <= r) {
        int m = l + (r - l) / 2;

        if (vector[m]->getId() == id)
            return vector.at(m);

        if (vector[m]->getId() < id)
            l = m + 1;

        else
            r = m - 1;
    }

    return nullptr;
}


void Node::addConnection(Connections *connection){
    connections.push_back(connection);
}

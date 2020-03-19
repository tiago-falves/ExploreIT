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

long int Node::getId(){
    return id;
}

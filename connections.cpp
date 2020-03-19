#include "connections.h"
#include <math.h>
#include <iostream>

double getDistance(Node *na,Node *nb){
    double raio = 6371000; // metres
    double a1 = na->getLatitude()*M_PI/180;
    double a2 = nb->getLatitude()*M_PI/180;
    double dLat = (nb->getLatitude()-na->getLatitude())*M_PI/180;
    double dLon = (nb->getLongitude()-na->getLongitude())*M_PI/180;

    double a = sin(dLat/2) * sin(dLat/2) +
            cos(a1) * cos(a2) *
            sin(dLon/2) * sin(dLon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));

    return raio * c;
}

Connections::Connections(Node *this_node,Node *next_node)
    :this_node(this_node),next_node(next_node)
{
    this->delta_h=next_node->getAltitude()-this_node->getAltitude();
    this->distance=getDistance(this_node,next_node);
}

Node *Connections::get_this_node(){

}

Node *Connections::get_next_node(){

}

double Connections::get_delta_h(){

}

double Connections::get_distance(){

}

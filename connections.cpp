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
    return this_node;
}

Node *Connections::get_next_node(){
    return next_node;
}

double Connections::get_delta_h(){
    return delta_h;
}

double Connections::get_distance(){
    return distance;
}
class W_node{
public:
    W_node(Node *actual,Node *before, double peso)
        :actual(actual),before(before),peso(peso)
    {
    }
    Node *actual;
    Node *before;
    double peso;

};

bool operator <(const W_node& a,const W_node& b){
    return a.peso<b.peso;
}

void explore(priority_queue<W_node> *linha,Node *last){
    W_node tempTop=linha->top();
    linha->pop();
    for(auto i:tempTop.actual->connections){
        Connections tempConnection(i->get_next_node(),last);
        W_node temp(i->get_next_node(),i->get_this_node(),i->get_distance()/5000*3600+tempTop.peso+tempConnection.get_distance()/5000*3600);
        linha->push(temp);
    }
}

void Way::getShortestPath(){

    priority_queue<W_node> linha;
    linha.push(W_node(initial,nullptr,0));
    explore(&linha,(end));
}


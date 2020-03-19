#ifndef NODE_H
#define NODE_H

#include <vector>
#include <connections.h>

using namespace std;

class Node
{
public:
    Node(double longitude,double latitude,double altitude,long unsigned id);
    double getLongitude();
    double getLatitude();
    double getAltitude();
    long int getId();
private:
    double longitude,latitude,altitude;
    const long unsigned id;
    vector<Connections> connections;
};

#endif // NODE_H

#ifndef NODE_H
#define NODE_H

#include <vector>
#include <connections.h>

using namespace std;

class Connections;
class Node
{
public:
    Node(double longitude,double latitude,double altitude,long unsigned id);
    double getLongitude();
    double getLatitude();
    double getAltitude();
    long unsigned getId();
    static Node* findNode(long unsigned id,vector<Node*> vector);
    void addConnection(Connections *connection);
private:
    double longitude,latitude,altitude;
    const long unsigned id;
    vector<Connections*> connections;

};

bool operator <(Node &a,Node &b);

#endif // NODE_H

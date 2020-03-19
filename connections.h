#ifndef CONNECTIONS_H
#define CONNECTIONS_H
#include <node.h>

class Node;
class Connections
{
public:
    Connections(Node *this_node,Node *next_node);
    Node *get_this_node();
    Node *get_next_node();
    double get_delta_h();
    double get_distance();

private:
    Node *this_node;
    Node *next_node;
    double delta_h;
    double distance;
};

#endif // CONNECTIONS_H

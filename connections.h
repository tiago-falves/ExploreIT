#ifndef CONNECTIONS_H
#define CONNECTIONS_H
#include <node.h>
#include <queue>
#include <vector>

using namespace std;

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

class Way
{
public:
    Way(Node *initial,Node *end)
        :initial(initial),end(end)
    {
        getShortestPath();
    }
private:
    Node *initial;
    Node *end;
    vector<Node*> nodes;
    void getShortestPath();
};

#endif // CONNECTIONS_H

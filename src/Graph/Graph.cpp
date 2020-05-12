#include "Graph.h"
#include "../Utils/utils.h"
#include <chrono>
#include <queue>
#include <MutablePriorityQueue.h>

#define INF std::numeric_limits<double>::max()

unordered_map<long, Node *> Graph::getNodes(){
    return nodes;
}

Node* Graph::findNode(const int &id) const {
    unordered_map<long, Node*>::const_iterator it = nodes.find(id);
    return it == nodes.end() ? nullptr : it->second;
}

bool Graph::addNode(const int &id, int x, int y) {
    if (findNode(id) != nullptr) return false;
    Node * newNode = new Node(id, x, y);
    this->nodes.insert(pair<int,Node*>(id, newNode));
    return true;
}

bool Graph::addEdge(int edgeId, int origId, int destId) {
    Node * orig = findNode(origId);
    Node * dest = findNode(destId);
    if(orig == nullptr || dest == nullptr) return false;
    Edge * edge1 = orig->addEdge(edgeId,orig, dest);
    Edge * edge2 = dest->addEdge(edgeId+1,dest, orig);
    this->edges.insert(pair<int,Edge*>(edgeId, edge1));
    this->edges.insert(pair<int,Edge*>(edgeId+1, edge2));

    return true;
}

void Graph::initNodes(Node *origin,Node *target){
    for(auto node:nodes){
        node.second->setWeight(INF);
        node.second->setDist(INF);
        double dx=abs(target->getX()-node.second->getX());
        double dy=abs(target->getY()-node.second->getY());
        //node.second->setDistTarget(sqrt(dx*dx+dy*dy));
        node.second->setDistTarget(dx+dy);
        node.second->path = nullptr;
    }
    nodes[origin->getId()]->setDist(0);
    nodes[origin->getId()]->setWeight(0);

}

bool Graph::relax(Node *v,Node *w, double weight,long int targetDistance){
    if(abs(v->getWeight() + weight-targetDistance*37+w->getDistTarget()) < abs(w->getWeight()-targetDistance*37+w->getDistTarget()))
    {
        if(v->path != w) {
            w->setDist(abs(v->getWeight() + weight - targetDistance*37 + w->getDistTarget()));
            w->setWeight(v->getWeight() + weight);
            w->path = v;
            return true;
        } else
            return false;
    }
    else
        return false;
}

double Graph::Dijkstra(long int origin,long int  target,long int targetDistance){
    initNodes(nodes[origin],nodes[target]);
    MutablePriorityQueue q;
    q.insert((nodes[origin]));
    cout<<((nodes[origin])<(nodes[target]))<<endl;
    while( ! q.empty())
    {
        auto v = q.extractMin();
        v->visited = true;
        if (v == nodes[target]) {
            if((abs(v->getWeight()-targetDistance*37.0)/targetDistance/37.0)<0.10) {
                cout << "Peso: " << v->getWeight() << endl;
                break;
            }
        }
        for(auto e : v->getEdges())
        {
            auto oldDist = e->getDestination()->getDist();
            if(!e->getDestination()->visited && relax(v, e->getDestination(), e->getWeight(),targetDistance))
            {
                if(oldDist == INF)
                    q.insert(e->getDestination());
                else
                    q.decreaseKey(e->getDestination());
            }
        }
    }
    return 0;
}

vector<Node> Graph::getPath(long int origin,long int dest)
{
    vector<Node> res;
    Node *v = nodes[dest];
    if(v == nullptr)
        return res;
    else if (v->getDist() == INF)
        return res;
    for( ; v != nullptr; v = v->path)
        res.push_back(*v);
    return res;
}

void Graph::FloydWarshall() {
    cout << "Started FloydWarshall algorithm" << endl;

    double ** W;   // dist
    double **P;   // path
    vector<Node*> temp;
    unordered_map<long, Node*>::const_iterator it = nodes.begin();
    while(it != nodes.end()){
        temp.push_back(it->second);
        it++;
    }

    unsigned n = temp.size();
    W = new double *[n];
    P = new double *[n];
    for (unsigned i = 0; i < n; i++) {
        W[i] = new double[n];
        P[i] = new double[n];
        for (unsigned j = 0; j < n; j++) {
            W[i][j] = i == j ? 0 : INF;
            P[i][j] = -1;
        }
        for (auto e : temp[i]->getEdges()) {
            int j = find(temp.begin(), temp.end(), e->getDestination()) - temp.begin();
            W[i][j]  = e->getWeight();
            P[i][j]  = i;
        }
    }

    for(unsigned k = 0; k < n; k++)
        for(unsigned i = 0; i < n; i++)
            for(unsigned j = 0; j < n; j++) {
                if(W[i][k] == INF || W[k][j] == INF)
                    continue; // avoid overflow
                int val = W[i][k] + W[k][j];
                if (val < W[i][j]) {
                    W[i][j] = val;
                    P[i][j] = P[k][j];
                }
            }

    cout << "W: " << endl;
    printMatrix(W);
}

void Graph::printMatrix(double **matrix) {
    unsigned n = getNodes().size();

    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            cout << setw(15) << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::resetVisited(){
    for(pair<long,Node *> node : nodes){
        node.second->visited = false;
    }
}


void Graph::removeSymetricEdges(int id){
    Node * node = findNode(id);
    if(node != nullptr){
        //Remove symmetric edges
        for (Edge * edge : node->getEdges()) {
            edge->getDestination()->removeEdge(id);
        }
    }
}

void Graph::removeUnvisited(Graph * graph){
    std::unordered_map<long, Node*>::iterator it = nodes.begin();
    while(it != nodes.end()){
        if(!it->second->visited){
            removeSymetricEdges(it->first);
            it = nodes.erase(it); //Remove from graph
        } else it++;
    }
    resetVisited();
}

void Graph::DFSConnectivity(int id) {
    Node * node = findNode(id);
    if(node != nullptr){
        resetVisited();
        DFSVisit(node);
    }
}

void Graph::DFSVisit(Node * node) {
    node->visited = true;
    for (Edge * edge : node->getEdges())
        if (!edge->getDestination()->visited)
            DFSVisit(edge->getDestination());
}

Edge * Graph::getSymetricEdge(Edge * edge){
    return edge->getDestination()->findEdge(edge->getOrigin()->getId());
}


const unordered_map<long,Edge*> Graph::getEdges(){
    return edges;
}
void Graph::setEdges(const unordered_map<long, Edge*> edges) {
    Graph::edges = edges;
}


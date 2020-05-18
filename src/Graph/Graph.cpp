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

bool Graph::addEdgeDiff(const int &id, int diff){
    this->edgeDiff.insert(pair<int,int>(id, diff));
    return true;
}


bool Graph::addEdge(int edgeId, int origId, int destId,int difficulty) {
    Node * orig = findNode(origId);
    Node * dest = findNode(destId);
    if(orig == nullptr || dest == nullptr) return false;
    Edge * edge1 = orig->addEdge(edgeId,orig, dest,difficulty);
    Edge * edge2 = dest->addEdge(edgeId+1,dest, orig,difficulty);
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

bool Graph::relax(Node *v,Node *w, double weight, long int targetDistance, int edge_difficulty, int difficulty){
    if(abs(v->getWeight() + weight-targetDistance*37+w->getDistTarget()) + abs(edge_difficulty - difficulty)
           < abs(w->getWeight()-targetDistance*37+w->getDistTarget()) + abs(edge_difficulty - difficulty))
    {
        if(v->path != w /*&& difficultyRange(difficulty, edge_difficulty)*/) {
            w->setDist(abs(v->getWeight() + weight - targetDistance*37 + w->getDistTarget()) + abs(edge_difficulty - difficulty));
            w->setWeight(v->getWeight() + weight + edge_difficulty);
            w->path = v;
            return true;
        } else
            return false;
    }
    else
        return false;
}

double Graph::AStar(long int origin,long int  target, long int targetDistance, int difficulty){
    initNodes(nodes[origin],nodes[target]);
    MutablePriorityQueue q;
    q.insert((nodes[origin]));
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
            if(!e->getDestination()->visited && relax(v, e->getDestination(), e->getWeight(), targetDistance, e->getDifficulty(), difficulty));
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

void Graph::FloydWarshall(string directory) {
    cout << "Started FloydWarshall algorithm" << endl;

    vector<Node*> temp;
    int vec_pos = 0;
    unordered_map<long, Node*>::const_iterator it = nodes.begin();
    while(it != nodes.end()){
        temp.push_back(it->second);
        it->second->setFloydPosition(vec_pos);
        it++; vec_pos++;
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

    ofstream file; file.open(directory + "floydWarshallOutput.txt");
    if (file.is_open()) {
        printMatrix(W, file);
        file.close();
    }else cout << "Unable to open Floyd Warshall output file!" << endl;

    //cout << getNodeDistance(0, 2) << endl;
}

void Graph::printMatrix(double **matrix, ostream& ost) {
    unsigned n = getNodes().size();

    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (matrix[i][j] == INF) ost << -1 << " ";
            else ost << matrix[i][j] << " ";
        }
        ost << endl;
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


unordered_map<int,int> Graph::getEdgeDiff(){
    return edgeDiff;
}

void Graph::setEdgeDiff(const unordered_map<int,int> edgeDiff){
    Graph::edgeDiff = edgeDiff;
}

bool Graph::difficultyRange(int difficulty, int edge_difficulty) {
    return edge_difficulty >= 0 && edge_difficulty <= difficulty + 1;
}

Edge *Graph::findEdge(Node orig, Node dest) {
    for (Edge* e : orig.getEdges()) {
        if (e->getDestination()->getId() == dest.getId()) return e;
    }
    return NULL;
}

int Graph::getNodeDistance(int origid, int destid) {
    return W[nodes.at(origid)->getFloydPostion()][nodes.at(destid)->getFloydPostion()];
}


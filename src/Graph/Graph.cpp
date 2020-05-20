#include "Graph.h"
#include "../Utils/utils.h"
#include <queue>
#include <MutablePriorityQueue.h>
#include <cfloat>
#include <chrono>

#define INF std::numeric_limits<double>::max()

unordered_map<long, Node *> Graph::getNodes(){
    return nodes;
}
vector<unordered_set<int>> Graph::getGraphs(){
    return graphs;
}

Node* Graph::findNode(const int &id) const {
    unordered_map<long, Node*>::const_iterator it = nodes.find(id);
    return it == nodes.end() ? nullptr : it->second;
}

Edge* Graph::findEdge(const int &id) const{
    unordered_map<long, Edge*>::const_iterator it = edges.find(id);
    return it == edges.end() ? nullptr : it->second;
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
        node.second->setSummedDifficulties(0);
        node.second->visited= false;
        node.second->violated_difficulty=false;
        double dx=abs(target->getX()-node.second->getX());
        double dy=abs(target->getY()-node.second->getY());
        //node.second->setDistTarget(sqrt(dx*dx+dy*dy));
        node.second->setDistTarget(dx+dy);
        node.second->path = nullptr;
    }
    nodes[origin->getId()]->setDist(0);
    nodes[origin->getId()]->setWeight(0);

}

bool Graph::relax(Node *v,Node *w, double tam_edge, long int targetDistance, int edge_difficulty, int difficulty){
    double ave_diff = (v->getSummedDifficulties()+edge_difficulty*tam_edge)/(v->getDist()+tam_edge);
    double localWeight = 0.9*abs(v->getDist()+tam_edge + w->getDistTarget() - targetDistance)/targetDistance + 0.1*abs(float(ave_diff/5));
    if(edge_difficulty<=difficulty+2)
    {
        if((localWeight < w->getWeight()) && v->path != w) {
            w->setDist( v->getDist()+tam_edge);
            w->setWeight(localWeight);
            w->path = v;
            w->violated_difficulty= false;
            w->setSummedDifficulties((v->getSummedDifficulties()+edge_difficulty*tam_edge));
            return true;
        }
    }
    else {
        localWeight = 0.9*abs(v->getDist()+tam_edge + w->getDistTarget() - targetDistance)/targetDistance + 4*abs(float(ave_diff/5));
        if ((localWeight < w->getWeight()) && v->path != w) {
            w->setDist(v->getDist() + tam_edge);
            w->setWeight(localWeight);
            w->path = v;
            w->violated_difficulty= true;
            w->setSummedDifficulties((v->getSummedDifficulties()+edge_difficulty*tam_edge));
            return true;
        }
    }
    return false;
}

double Graph::AStar(long int origin,long int  target, long int targetDistance, int difficulty){
    cout << "Started A*: Origin" << origin << " Destiny: " << target << endl;
    initNodes(nodes[origin],nodes[target]);
    MutablePriorityQueue q;
    q.insert((nodes[origin]));
    while( ! q.empty())
    {
        auto v = q.extractMin();
        v->visited = true;
        if (v == nodes[target]) {
            if((abs(v->getDist()-targetDistance)/targetDistance)<0.10) {
                return 0;
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
    //cout << "Peso: " << nodes[target]->getDist()<< " " << targetDistance << endl;
    return 0;
}

bool Graph::calculateInterestingPath(vector<int> confluencePoints,vector<int> hours, vector<int> difficulties,int TMax){

    cout << "Started Algorithm\n";
    if(confluencePoints.size() != hours.size()){
        cout << "Each point does not have a corresponding hour\n";
        return false;
    }
    for (int i = 0; i < confluencePoints.size()-1; ++i) {
        for (int j = 0; j < difficulties.size(); ++j) {
            AStar(confluencePoints[i],confluencePoints[i+1],hours[i+1]-hours[i],difficulties[i]);
        }

    }
    return true;
}

vector<Node> Graph::getPath(long int origin,long int dest)
{
    vector<Node> res;
    Node *v = nodes[dest];
    float sum=0;
    if(v == nullptr)
        return res;
    else if (v->getDist() == INF)
        return res;
    for( ; v != nullptr; v = v->path) {
        if(v->violated_difficulty){
            std::string cont;
            cout<<"Difficulty was violated at point "<<v->getId()<<", press enter to continue:"<<endl;
            //getline(cin,cont);
        }
        res.push_back(*v);
        sum+=v->getDist();
    }
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

}

void Graph::printMatrix(double **matrix, ostream& ost) {
    auto start = std::chrono::high_resolution_clock::now();
    unsigned n = getNodes().size();

    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (matrix[i][j] == INF) ost << -1 << " ";
            else ost << matrix[i][j] << " ";
        }
        ost << endl;
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Write time: " << elapsed.count() << " s\n" << endl;
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
    for (Edge * edge : node->getEdges()) {
        if (!edge->getDestination()->visited)
            DFSVisit(edge->getDestination());
    }
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

void Graph::setGraphs(const vector<unordered_set<int>> &graphs) {
    Graph::graphs = graphs;
}
int  Graph::getMostConnected(){
    int max = 0;
    int index;
    for (int i = 0; i < graphsVector.size() ; ++i) {
        if(graphsVector[i].size() >= max) {
            max = graphsVector[i].size();
            index = i;
        }
    }
    return index;
}

int  Graph::getNodeConnectedGraph(int node){
    int index = -1;
    for (int i = 0; i < graphs.size() ; ++i) {
        if(graphs[i].find(node) != graphs[i].end()){
            index = i;
            return index;
        }
    }
    return index;
}

bool  Graph::isInConnectedGraph(int index,int node){
    if(graphs[index].find(node) != graphs[index].end()){
        return true;
    }
    return false;
}

const vector<vector<int>> &Graph::getGraphsVector() const {
    return graphsVector;
}

void Graph::setGraphsVector(const vector<vector<int>> &graphsVector) {
    Graph::graphsVector = graphsVector;
}






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

void Graph::initNodes(Node *origin,Node *target,vector<Node> *nodesVisited){


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
        node.second->setSummedDifficulties(0);
    }
    if(nodesVisited != nullptr){
        for(auto i:*nodesVisited){
            nodes[i.getId()]->visited = true;
        }
    }

    nodes[origin->getId()]->visited = false;
    nodes[target->getId()]->visited = false;

    nodes[origin->getId()]->setDist(0);
    nodes[origin->getId()]->setWeight(0);

}

bool Graph::relax(Node *v,Node *w, double tam_edge, long int targetDistance, int edge_difficulty, int difficulty){
    //Average difficulty
    double ave_diff = (v->getSummedDifficulties()+edge_difficulty*tam_edge)/(v->getDist()+tam_edge);

    //Calculo da distancia v->getDist()+tam_edge + w->getDistTarget() - targetDistance)/targetDistance
    //Pegas na soma atual somas a distancia aproximada
    //Target distance
    //Soma atual v->getDist()+tam_edge


    double localWeight = 0;

    if(w->getTags().size()) {
        localWeight = 0.9 * abs(v->getDist() + tam_edge + w->getDistTarget() - targetDistance) / targetDistance +
                      0.1 * abs(float((ave_diff-difficulty) / ave_diff));
    }
    else{
        localWeight = 0.9 * abs(v->getDist() + tam_edge + w->getDistTarget() - targetDistance) / targetDistance +
                      0.1 * abs(float((ave_diff-difficulty) / ave_diff))+1;
    }


    //Se dificuldade for 5 entao varia entre 3 e 7 entra neste if
    if(abs(edge_difficulty-difficulty)<=2)
    {
        // Isto e a função de relax
        if((localWeight < w->getWeight()) && v->path != w) {
            w->setDist( v->getDist()+tam_edge);
            w->setWeight(localWeight);
            w->path = v;
            w->violated_difficulty= false;
            w->setSummedDifficulties((v->getSummedDifficulties()+edge_difficulty*tam_edge));
            return true;
        }
    }
        //Caso a dificuldade for violada
    else if(abs(edge_difficulty-difficulty)<=4 || edge_difficulty-difficulty < 0){
        //Ele adiciona mais valor a dificuldade

        if(w->getTags().size()) {
            localWeight = (0.9*abs(v->getDist()+tam_edge + w->getDistTarget() - targetDistance)/targetDistance + 4*abs(float((ave_diff-difficulty) / ave_diff)));
        }
        else{
            localWeight = (0.9*abs(v->getDist()+tam_edge + w->getDistTarget() - targetDistance)/targetDistance + 4*abs(float((ave_diff-difficulty) / ave_diff))+1);
        }

        if ((localWeight < w->getWeight()) && v->path != w) {
            w->setDist(v->getDist() + tam_edge);
            w->setWeight(localWeight);
            w->path = v;
            w->violated_difficulty= true;
            w->setSummedDifficulties((v->getSummedDifficulties()+edge_difficulty*tam_edge));
            return true;
        }
    }
    else {
        //Ele adiciona mais valor a dificuldade

        if(w->getTags().size()) {
            localWeight = (0.9*abs(v->getDist()+tam_edge + w->getDistTarget() - targetDistance)/targetDistance + 8*abs(float((ave_diff-difficulty) / ave_diff)));
        }
        else{
            localWeight = (0.9*abs(v->getDist()+tam_edge + w->getDistTarget() - targetDistance)/targetDistance + 8*abs(float((ave_diff-difficulty) / ave_diff))+1);
        }

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

bool Graph::relaxDijkstra(Node *node, Edge * edge) {//Vertex *w, double weight) {
    double weight = edge->getWeight();
    Node * w = edge->getDestination();
    if (node->getDist() + weight < w->getDist()) {
        w->setDist(node->getDist() + weight);
        w->path = node;
        return true;
    }
    else
        return false;
}

void Graph::dijkstraShortestPath(const int &source, const int &dest){
    Node * start = nodes[source];
    Node * end = nodes[dest];
    initNodes(start,end);
    MutablePriorityQueue q;
    q.insert(start);
    while( ! q.empty() ) {
        Node* v = q.extractMin();
        v->visited = true;

        if (v->getId() == dest) return;

        for(Edge * e : v->getEdges()) {
            double oldDist = e->getDestination()->getDist();
            if (relaxDijkstra(v, e)) {//e.dest, e.weight)) {
                if (oldDist == INF)
                    q.insert(e->getDestination());
                else
                    q.decreaseKey(e->getDestination());
            }
        }
    }
}

double Graph::AStar(long int origin,long int  target, long int targetDistance, int difficulty,vector<Node> *nodesVisited){
    cout << "Difficuldade: "<<difficulty << endl;
    cout << "Started A*\n";
    cout <<  "\tOrigin: " << origin << endl;
    cout << " \tDestiny: " << target << endl;
    cout << " \tTarget Distance: " << targetDistance << endl;
    initNodes(nodes[origin],nodes[target],nodesVisited);
    MutablePriorityQueue q;
    q.insert((nodes[origin]));
    while( ! q.empty())
    {
        auto v = q.extractMin();
        v->visited = true;
        if (v == nodes[target]) {
            if((abs(v->getDist()-targetDistance)/targetDistance)<0.10) {
                pointsToDraw.push_back(getPath(origin,target));
                cout <<"Real Size: " << pointsToDraw.back().size() <<endl;
                return 0;
            }
        }
        for(auto e : v->getEdges())
        {
            auto oldDist = e->getDestination()->getDist();
            if(!e->getDestination()->visited)
            {
                if(relax(v, e->getDestination(), e->getWeight(), targetDistance, e->getDifficulty(), difficulty)) {
                    if (oldDist == INF) {
                        q.insert(e->getDestination());
                    }
                    else {
                        q.decreaseKey(e->getDestination());
                    }
                }
            }
            else if(relax(v, e->getDestination(), e->getWeight(), targetDistance, e->getDifficulty(), difficulty*100)){
                if (oldDist == INF) {
                    q.insert(e->getDestination());
                }
                else {
                    q.decreaseKey(e->getDestination());
                }
            }
        }
    }

    pointsToDraw.push_back(getPath(origin,target));
    cout <<"Real Size: " << pointsToDraw.back().size() <<endl;

    return 0;


}

bool Graph::calculateInterestingPath(vector<int> confluencePoints,vector<int> hours, vector<int> difficulties,int TMax){

    cout << "Started Algorithm\n";
    if(confluencePoints.size() != hours.size()){
        cout << "Each point does not have a corresponding hour\n";
        return false;
    }
    cout << endl;

    for (int i = 0; i < confluencePoints.size() - 1; ++i) {
        cout << confluencePoints.at(i);
    }
    cout << endl;
    for(auto d:difficulties) {
        for (int i = 0; i < confluencePoints.size() - 1; ++i) {
            vector<Node> nodes;
            for(int i1=i-1;i1>=0;i1--){
                nodes.insert(nodes.end(),pointsToDraw.at(i1).begin(),pointsToDraw.at(i1).end());
            }
            if(i==0)
                AStar(confluencePoints[i], confluencePoints[i + 1], hours[i + 1] - hours[i], d);
            else{
                AStar(confluencePoints[i], confluencePoints[i + 1], hours[i + 1] - hours[i], d,&nodes);
            }
            if(!pointsToDraw.back().size()){
                AStar(confluencePoints[i], confluencePoints[i + 1], hours[i + 1] - hours[i], d);
            }
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
        if(v->path != nullptr) {
            Edge *ed = findEdge(*v, *v->path);
            if (ed != nullptr)
                cout << ed->getDifficulty() << endl;
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








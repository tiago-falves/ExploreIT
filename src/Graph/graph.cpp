#include "graph.h"
#include "../Utils/utils.h"
#include <chrono>
#include <queue>


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

bool Graph::addEdge(int origId, int destId) {
    Node * orig = findNode(origId);
    Node * dest = findNode(destId);
    if(orig == nullptr || dest == nullptr) return false;

    orig->addEdge(orig, dest);
    dest->addEdge(dest, orig);
    return true;
}

bool operator <(ww a,ww b){
    return a.second>b.second;
}

bool operator <(Node a,Node b){
    return a.getId()<b.getId();
}

typedef unordered_map<Node*,double, setpHash, setpHash> d;
typedef unordered_map<Node*,Node*, setpHash, setpHash> p;
typedef unordered_set<Node*, setpHash, setpHash> n;


vector<Edge*> Graph::getEdges(){
    return edges;
};

double Graph::Dijkstra(){
    string carry;// The main loop
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    cout<<endl<<"Start Dijkstra!!"<<endl;
    Node source=(*nodes.find(0)->second);
    Node target=(*nodes.find(284)->second);
    d dist;
    p prev;
    priority_queue<ww> Q;
    n n_c;

    dist[&source] = 0;
    Node tmp_n;
    for(auto v:nodes){
        if((v.second->getId() != source.getId())){
            dist[v.second] = 9000000900000000000;
            prev[v.second] = &tmp_n;
        }

        Q.push(ww(v.second,dist[v.second]));
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout<<"Load Done!! "<<std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()/1000000.0<<endl<<endl;

    cout<<"Starting"<<endl<<flush;
    begin = std::chrono::steady_clock::now();
    Node *bef;
    while(!Q.empty()){
        auto u=Q.top();
        Q.pop();
        if(u.second==9000000900000000000){
            //return 0;
            //dist[u.first]=0;
            end = std::chrono::steady_clock::now();
            cout<<"Dijkstra Ended!! "<<std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()/1000000.0<<endl;
            break;
        }
        if(u.first->getId()!=target.getId()){
            if(n_c.find(u.first)==n_c.end()){
                for(auto v:u.first->getEdges()){
                    if(n_c.find(v->getDestination())==n_c.end()){
                        double alt = dist[u.first] + v->getWeight();
                        if(alt < dist[v->getDestination()]){
                            dist[v->getDestination()] = alt;
                            prev[v->getDestination()] = u.first;
                            ww tmp(v->getDestination(),alt);
                            Q.push(tmp);
                        }
                        n_c.insert(u.first);
                    }
                }
            }
        }
        else {
            //cout<<u.second<<" "<<u.first->getId()<<endl;
        }
        cout<<u.second<<" "<<u.first->getId()<<endl;
        bef=u.first;
    }
    Node* tmp=bef;
    while (tmp->getId()!=source.getId()){
        edges.push_back(new Edge(tmp,prev[tmp],1));
        tmp=prev[tmp];
    }
    return 0;
}

#include "graph.h"
#include "src/utils.h"
#include <chrono>
#include <queue>



unordered_map<long, Node *> Graph::getNodes(){
    return nodes;
}

Graph::Graph(){

    string ask;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    cout<<"Start!"<<endl;
    nodes.reserve(2000000);
    cout<<"Nodes Start!"<<endl;
    fstream file_node("data/nodes.txt");
    string in;
    getline(file_node,in);
    while (getline(file_node,in)) {
        string temp=in.substr(1,in.size()-3);
        vector<double> tmp_vector=getSubStr(temp);
        nodes[tmp_vector.at(0)]=new Node(tmp_vector.at(0),tmp_vector.at(1),tmp_vector.at(2));
    }
    file_node.close();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    cout<<"Nodes Ended!! "<<std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()/1000000.0<<endl;

    begin = std::chrono::steady_clock::now();
    fstream file_edges("data/edges.txt");
    getline(file_edges,in);
    cout<<"Edges Start!"<<endl;
    while (getline(file_edges,in)) {
        string temp=in.substr(1,in.size()-3);
        vector<double> tmp_vector=getSubStr(temp);
        Node *a=(nodes.find(tmp_vector.at(0)))->second;
        Node *b=(nodes.find(tmp_vector.at(1)))->second;
        if(a!=NULL && b!=NULL){
            a->addEdge(b);
            b->addEdge(a);
        }
    }
    end = std::chrono::steady_clock::now();
    cout<<"Edges Ended!! "<<std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()/1000000.0<<endl;

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

double Graph::Dijkstra(){
    string carry;// The main loop
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    cout<<endl<<"Start Dijkstra!!"<<endl;
    Node source=(*nodes.find(26018641)->second);
    Node target=(*nodes.find(26018620)->second);
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
    while(!Q.empty()){
        auto u=Q.top();
        Q.pop();
        if(u.second==9000000900000000000){
            //return 0;
            //dist[u.first]=0;
            end = std::chrono::steady_clock::now();
            cout<<"Dijkstra Ended!! "<<std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()/1000000.0<<endl;
	    return 0;
        }
        if(u.first->getId()!=target.getId()){
            if(n_c.find(u.first)==n_c.end()){
                for(auto v:u.first->getEdges()){
                    if(n_c.find(v->getNode())==n_c.end()){
                        double alt = dist[u.first] + v->getDistance();
                        if(alt < dist[v->getNode()]){
                            dist[v->getNode()] = alt;
                            prev[v->getNode()] = u.first;
                            ww tmp(v->getNode(),alt);
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
    }
    return 0;
}

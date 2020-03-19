#include "mapparser.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <pugixml/pugixml.hpp>
#include <node.h>
#include <map>
#include <algorithm>
#include <GL/glut.h>

using namespace std;

inline bool sorter(Node *a,Node *b){
    return *a<*b;
}

MapParser::MapParser(int argc, char **argv)
{
    vector<Node*> nodes;
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("map.osm");

    if (!result)
        return;

    //iterate nodes
    for (pugi::xml_node tool: doc.child("osm").children("node"))
    {
        long unsigned id=(tool.attribute("id").as_llong());
        double latitude=(tool.attribute("lat").as_double());
        double longitude=(tool.attribute("lon").as_double());
        nodes.push_back(new Node(longitude,latitude,0,id));
    }
    sort(nodes.begin(),nodes.end(),sorter);

    for(auto i:nodes){
        //cout<<i->getId()<<endl;
    }

    //iterate ways
    for (pugi::xml_node way_it: doc.child("osm").children("way"))
    {
        for (pugi::xml_node node_it: way_it.children("nd"))
        {
            auto curr_no=node_it;
            auto next_no=node_it.next_sibling("nd");
            Node *a=Node::findNode(curr_no.attribute("ref").as_llong(),nodes);
            Node *b=Node::findNode(next_no.attribute("ref").as_llong(),nodes);

            if(b!=nullptr)
                a->addConnection(new Connections(a,b));
        }
    }

    //display map
    MapDisplay temp_map=MapDisplay(&nodes,argc,argv);
    temp_map.start();

}

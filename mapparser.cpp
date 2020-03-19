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

MapParser::MapParser(int argc, char **argv)
{
    vector<Node*> nodes;
    map<float,float> display_nos;
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("map.osm");
    map<long int,int> nos;
    if (!result)
        return;

    //iterate nodes
    for (pugi::xml_node tool: doc.child("osm").children("node"))
    {
        long unsigned id=(tool.attribute("id").as_llong());
        double latitude=(tool.attribute("lat").as_double());
        double longitude=(tool.attribute("lon").as_double());
        display_nos[(longitude+7.71536)*2000]=(latitude-40.2646)*2000;
        nodes.push_back(new Node(longitude,latitude,0,id));
    }

    //iterate ways
    for (pugi::xml_node way: doc.child("osm").children("way"))
    {
        for (pugi::xml_node node: way.children("nd"))
        {
            auto no=nos.find(node.attribute("ref").as_llong());
            if(no == nos.end()){
                nos[node.attribute("ref").as_llong()]=1;
            }
            else{
                no->second++;
            }
        }
    }

    //display map
    MapDisplay temp_map=MapDisplay(display_nos,argc,argv);
    temp_map.start();



}

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

map<float,float> display_nos;
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_POINTS);
    for(auto i:display_nos){
        cout<<i.first<<" "<<i.second<<endl;
        glVertex2f(i.first,i.second);
    }
    glEnd();
    glFlush();
}

void myinit(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(5.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 499.0, 0.0, 499.0);
}

MapParser::MapParser(int argc, char **argv)
{
    vector<Node*> nodes;
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("map.osm");
    map<long int,int> nos;
    if (!result)
        return;
    long int count=0;
    for (pugi::xml_node tool: doc.child("osm").children("node"))
    {
        long unsigned id=(tool.attribute("id").as_llong());
        double latitude=(tool.attribute("lat").as_double());
        double longitude=(tool.attribute("lon").as_double());
        /*std::cout << "Node " << id;
        cout<< " has latitude "<< latitude;
        cout<< " has longitude "<< longitude << "\n";*/
        display_nos[(longitude+7.71536)*2000]=(latitude-40.2646)*2000;

        nodes.push_back(new Node(longitude,latitude,0,id));
        count++;
    }
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

    vector<string> nos_string;
    for( auto i:nos){
        nos_string.push_back(to_string(i.second)+" "+to_string(i.first));
    }
    /*s
    sort(nos_string.begin(),nos_string.end());
    for(auto i:nos_string){
        std::cout << "Node "<< i<<endl;
    }*/
    cout<<count<<endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Points");
    glutDisplayFunc(display);

    myinit();
    glutMainLoop();
}

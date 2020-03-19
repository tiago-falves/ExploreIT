#ifndef MAPDISPLAY_H
#define MAPDISPLAY_H

#include <GL/glut.h>
#include <map>
#include <iostream>
#include <node.h>

using namespace std;

class MapDisplay
{
public:
    MapDisplay(vector<Node*> *mapa,int argc, char **argv);
    void start();
private:
    static void display();
    void myinit();
    static vector<Node*> *mapa;
};

#endif // MAPDISPLAY_H

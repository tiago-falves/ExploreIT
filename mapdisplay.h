#ifndef MAPDISPLAY_H
#define MAPDISPLAY_H

#include <GL/glut.h>
#include <map>
#include <iostream>

using namespace std;

class MapDisplay
{
public:
    MapDisplay(map<float,float> mapa,int argc, char **argv);
    void start();
private:
    static void display();
    void myinit();
    static map<float,float> mapa;
};

#endif // MAPDISPLAY_H

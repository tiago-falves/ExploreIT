#include "mapdisplay.h"


map<float,float> MapDisplay::mapa={};
void MapDisplay::display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_POINTS);
    for(auto i:mapa){
        cout<<i.first<<" "<<i.second<<endl;
        glVertex2f(i.first,i.second);
    }
    glEnd();
    glFlush();
}

void MapDisplay::myinit(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(5.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 499.0, 0.0, 499.0);
}

MapDisplay::MapDisplay(map<float,float> mapa,int argc, char **argv)
{
    this->mapa=mapa;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Points");
}

void MapDisplay::start(){
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
}





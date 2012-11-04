#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#endif
#include <cmath>
#include<vector>


using namespace std;



class primitives
{
public:
    primitives();
    static double filter(int distance);
    static void intensifyPixel(int x,int y,double distance);
};



//Clase Punto
class point2D
{

private:
    int x,y;
public:

    //Constructores
    point2D();
    point2D(int x,int y);

    //Sets y Gets
    void setpoint(int x,int y);
    void setX(int x);
    void setY(int y);
    int getx();
    int gety();
    void draw();

protected:


};

#endif // PRIMITIVES_H

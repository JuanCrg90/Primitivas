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
    static void drawPixel2D(int x, int y);
};


//Clase Linea
class line:public point2D
{
private:
    point2D v1,v2; //punto de inicio, punto final
public:
    //Constructores
    line();
    line(point2D v1,point2D v2);
    line(int x1,int y1, int x2,int y2);
    void drawLine(); //Algoritmo incremental



};


#endif // PRIMITIVES_H

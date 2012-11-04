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
    int t; //grosor

    void thick1(int x,int y,float m,int t);
    void boundaryFill(int x,int y,int t);

public:
    //Constructores
    line();
    line(point2D v1,point2D v2);
    line(int x1,int y1, int x2,int y2);
    //sets y gets
    void setLine(point2D v1,point2D v2);

    void setV1(int x,int y);
    void setV1(point2D v1);

    void setV2(int x,int y);
    void setV2(point2D v2);

    void setThick(int t);

    //Primitivas pintado
    void drawLine(); //Algoritmo incremental (incluye Fill2
    void midPointLine(); //Algoritmo de punto medio

    //Antialiasing
    void midPointLineAntialiasing(); //Linea con antialiasing usando algoritmo de punto medio


    //grosor (Fill)
    void Fill();
    void Fill2();







};


#endif // PRIMITIVES_H

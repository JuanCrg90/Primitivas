#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#endif
#include <math.h>


class primitives
{
public:
    primitives();
};



//Clase Punto
class point
{
public:
    float x,y;
    void drawPixel2D(int x,int y); //Dibuja Pixel en 2 dimensiones



protected:
    double filter(int distance);
    void intensifyPixel(int x,int y,double distance);

};

//Clase Linea
class line:point
{
private:
    point p1,p2; //vertice inicial y final
public:
    void DrawLine(int x0, int y0,int x1,int y1); //Algoritmo Incremental
    void DrawLineFill(int x0, int y0,int x1,int y1,int t);
    void DrawLineFill2(int x0, int y0, int x1, int y1, int t);


    void midPointLine(int x0,int y0, int x1, int y1); //Algoritmo de punto medio
    void midPointLineAntialiasing(int x0,int y0, int x1, int y1); //antialiasing


private:
    void thick1(int x,int y,float m,int t);
    void boundaryFill(int x,int y,int t);//coordenadas de la recta,pendiente,grosor
};



class ellipse:point
{
private:
    void EllipsePoints(int x, int y); //Puntos que conforman la elipse
public:
    void midPointEllipse(int a, int b); //Algoritmo del punto medio
};


class circle:point
{
private:
    void circlePoints(int x,int y); //puntos que conforman el circulo
public:

    void midPointCircle(int radius); //Algoritmo de punto medio
    void secondOCircle(int radius); //Algoritmo de Segundo Orden



};


#endif // PRIMITIVES_H

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
#include <algorithm>

#include <QDebug>

using namespace std;

class line;
class point2D;

class primitives
{
private:
    enum{TOP=0x1,BOTTOM=0x2,RIGHT=0x4,LEFT=0x8};
    typedef unsigned int uint;
    static uint endPointCode(double x,double y,double xMin,double xMax,double yMin,double yMax);
    //Recortado de poligonos
    vector<point2D> SutherlandHodgman(vector<point2D> in,line l,int pos);
    /*
      Devuelve vector de puntos despues de la interseccion, recibe
      Vector de puntos inicial, linea de escaneo, orientacion de la linea de escaneo (vert=0,hor=1)
      */


public:
    primitives();
    static double filter(int distance);
    static void intensifyPixel(int x,int y,double distance);
    static bool intersectRect(line scan,point2D C,point2D D); //comprueba si hay interseccion entre dos segmentos de recta
    static point2D intersectHor(line scan,point2D A,point2D B); //interseccion contra linea horizontal
    static point2D intersectVer(line scan,point2D A,point2D B); //interseccion contra linea vertical
    static bool inside(point2D P0,point2D P1,point2D P2); //Punto a evaluar, Recta P1P2


    //Recortado de lineas p0(x0,y0) p1(x1,y1) rectangulo diagonal xMin yMin a xMax yMax
    static void cohenSutherlandClippingLine(double x0,double y0,double x1, double y1,double xMin,double xMax,double yMin, double yMax);

    //Recortado de poligonos


    //Condiciones para STL
    static bool condicion(point2D A, point2D B); //condición para ordenamiento mediante sort de stl
    static bool uniqueTest(point2D A, point2D B); //condicion para comprobación de elementos repetidos usando STL unique


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

    int getXv1();
    int getYv1();

    int getXv2();
    int getYv2();

    point2D getV1();
    point2D getv2();



    //Primitivas pintado
    void drawLine(); //Algoritmo incremental (incluye Fill2)
    void midPointLine(); //Algoritmo de punto medio

    //Antialiasing
    void midPointLineAntialiasing(); //Linea con antialiasing usando algoritmo de punto medio

    //grosor (Fill)
    void Fill();
    void Fill2();
protected:
    void drawLine(int x0,int y0,int x1,int y1); //Algoritmo incremental (incluye Fill2)

};

class Circle:public point2D
{
private:
    int radius;
    void circlePoints(int x,int y); //puntos que conforman el circulo
public:
    //Constructores
    Circle();
    Circle(int r);
    //sets y gets
    void setRadius(int r);
    int getRadius();

    //Primitivas de pintado
    void midPointCircle(); //Algoritmo de punto medio
    void secondOCircle(); //Algoritmo de Segundo Orden
};

class Ellipse:public line
{
private:
    int a,b;

    void EllipsePoints(int x, int y);
public:
    //Constructores
    Ellipse();
    Ellipse(int a,int b);

    //sets y gets
    void setAB(int a,int b);
    void setA(int a);
    void setB(int b);

    int getA();
    int getB();

    //Primitivas de pintado
    void midPointEllipse();

    //Rellenado
    void fill();


};



class Rectangle:public line
{
private:
    vector<point2D> points;
    bool fill;

public:
    //constructores
    Rectangle();
    Rectangle(point2D p1,point2D p2,point2D p3, point2D p4);
    Rectangle(point2D p1,point2D p2,point2D p3, point2D p4,bool fill);
    //sets y gets
    void setP1(point2D p);
    void setP1(int x,int y);

    void setP2(point2D p);
    void setP2(int x,int y);

    void setP3(point2D p);
    void setP3(int x,int y);

    void setP4(point2D p);
    void setP4(int x,int y);

    void setFill(bool fill);

    vector<point2D> getRectangle();
    point2D getP1();
    point2D getP2();
    point2D getP3();
    point2D getP4();
    bool getFillStatus();

    //primitiva de pintado
    void draw();
};

class Polygon:public line
{
private:
    vector<point2D> points;
    bool fill;

    void polygonFill();

public:
    //Constructores
    Polygon();

    //sets y gets
    void setpoint(point2D p);
    void setpoint(int x, int y);
    void setFill(bool fill);

    point2D getPoint(int index);
    bool getFillStatus();

    //Primitiva Pintado
    void draw();
};




#endif // PRIMITIVES_H

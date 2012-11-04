#include "primitives.h"

primitives::primitives()
{
}


double primitives::filter(int distance)
{
    //0.5 ->desviación estandar pendiente calcular
        //return exp(-distance)/(2*0.5);
        return 0.5999+0.120*distance+0.6819*(distance*distance)+0.2824*(distance*distance*distance);
}


void primitives::intensifyPixel(int x, int y, double distance)
{
    double intensity=filter(distance);
    glColor3f(intensity,intensity,intensity);
}


point2D::point2D()
{
    this->x=0;
    this->y=0;
}

point2D::point2D(int x, int y)
{
    this->x=x;
    this->y=y;
}

void point2D::setpoint(int x, int y)
{
    this->x=x;
    this->y=y;
}

void point2D::setX(int x)
{
    this->x=x;
}

void point2D::setY(int y)
{
    this->y=y;
}

int point2D::getx()
{
    return x;
}

int point2D::gety()
{
    return y;
}

void point2D::draw()
{
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}
















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


bool primitives::intersectRect(line scan, point2D C, point2D D)
{


    point2D A,B;
    float r;
    float s;

    A.setX(scan.getV1().getx());
    A.setY(scan.getV1().gety());

    B.setX(scan.getv2().getx());
    B.setY(scan.getv2().gety());

    /*

            (Ay-Cy)(Dx-Cx)-(Ax-Cx)(Dy-Cy)
        r = -----------------------------  (eqn 1)
            (Bx-Ax)(Dy-Cy)-(By-Ay)(Dx-Cx)

            (Ay-Cy)(Bx-Ax)-(Ax-Cx)(By-Ay)
        s = -----------------------------  (eqn 2)
            (Bx-Ax)(Dy-Cy)-(By-Ay)(Dx-Cx)

*/

    float r_numerator=((B.getx()-A.getx())*(D.gety()-C.gety())-(B.gety()-A.gety())*(D.getx()-C.getx()));
    float s_numerator=((B.getx()-A.getx())*(D.gety()-C.gety())-(B.gety()-A.gety())*(D.getx()-C.getx()));


    if(r_numerator!=0 && s_numerator!=0)
    {
        r=((A.gety()-C.gety())*(D.getx()-C.getx())-(A.getx()-C.getx())*(D.gety()-C.gety()))/r_numerator;
        s=((A.gety()-C.gety())*(B.getx()-A.getx())-(A.getx()-C.getx())*(B.gety()-A.gety()))/s_numerator;
    }
    else
    {
        return false;
    }
    /*
 If 0<=r<=1 & 0<=s<=1, intersection exists
            r<0 or r>1 or s<0 or s>1 line segments do not intersect
            */


    if(0<=r && r<=1 && 0<=s && s<=1)
    {
        return true;
    }
    return false;
}


point2D primitives::intersectHor(line scan, point2D A, point2D B)
{
    point2D intersect;

    intersect.setX(A.getx()+(B.getx()-A.getx())*(scan.getV1().gety()-A.gety())/(B.gety()-A.gety()));
    intersect.setY(scan.getV1().gety());

    return intersect;

}

point2D primitives::intersectVer(line scan, point2D A, point2D B)
{
    point2D intersect;

    intersect.setX(A.gety()+(B.gety()-A.gety())/(B.getx()-A.getx())*(scan.getV1().getx()-A.getx()));
    intersect.setY(scan.getV1().getx());

    return intersect;
}

bool primitives::condicion(point2D A, point2D B)
{
    return A.getx()<B.getx();
}


bool primitives::uniqueTest(point2D A, point2D B)
{
    return A.getx()==B.getx();
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



void point2D::drawPixel2D(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}



line::line()
{
    v1.setpoint(0,0);
    v2.setpoint(0,0);
    t=1;
}

line::line(point2D v1, point2D v2)
{
    this->v1=v1;
    this->v2=v2;
    t=1;
}

void line::setLine(point2D v1, point2D v2)
{
    this->v1=v1;
    this->v2=v2;
    t=1;
}



line::line(int x1, int y1, int x2, int y2)
{
    this->v1.setX(x1);
    this->v1.setY(y1);

    this->v2.setX(x2);
    this->v2.setY(y2);

    t=1;

}


void line::setV1(int x, int y)
{
    this->v1.setpoint(x,y);
}


void line::setV1(point2D v1)
{
    this->v1.setpoint(v1.getx(),v1.gety());
}


void line::setV2(int x, int y)
{
    this->v2.setpoint(x,y);
}

void line::setV2(point2D v2)
{
    this->v2.setpoint(v2.getx(),v2.gety());
}

void line::setThick(int t)
{
    this->t=t;
}


int line::getXv1()
{
    return v1.getx();
}

int line::getYv1()
{
    return v1.gety();
}

int line::getXv2()
{
    return v2.getx();
}

int line::getYv2()
{
    return v2.gety();
}

point2D line::getV1()
{
    return v1;
}

point2D line::getv2()
{
    return v2;
}




void line::thick1(int x, int y, float m, int t)
{
    int i=0;

    glBegin(GL_POINTS);
    if(m>-1.0 && m<1.0)
    {
        if(t>1)
        {
            for(i=-t/2;i<t/2;i++)
                glVertex2i(x,y+i);
        }
        else
            glVertex2i(x,y);
    }
    else
    {
        if(t>1)
        {
            for(i=-t/2;i<t/2;i++)
                glVertex2i(x+i,y);
        }
        else
            glVertex2i(x+i,y);

    }
    glEnd();

}


void line::boundaryFill(int x, int y, int t)
{
    int i,j;

    if(t==1)
        drawPixel2D(x,y);
    else
    {
        for(i=-t/2;i<t/2;i++)
        {
            for(j=-t/2;j<t/2;j++)
            {
                drawPixel2D(x+i,y+j);
            }
        }
    }



}




void line::drawLine()
{
    int x0=v1.getx();
    int x1=v2.getx();

    int y0=v1.gety();
    int y1=v2.gety();


    double dx=x1-x0;
    double dy=y1-y0;

    double m= dy/dx;
    float y=y0;
    float x;

    if(m<=1)
    {
        if(dx!=0)
        {

            if(x1>=x0)
            {
                for(x=x0;x<x1;x+=1)
                {
                    boundaryFill(x,floor(y+0.5),t);
                    y+=m;
                }
            }
            else
            {
                for(x=x0;x>x1;x--)
                {
                    boundaryFill(x,floor(y+0.5),t);
                    y-=m;
                }
            }

        }
        else
        {
            x=x0;
            if(y1>=y0)
            {
                for(y=y0;y<y1;y++)
                {
                    boundaryFill(x,floor(y+0.5),t);
                    y++;
                }
            }
            else
            {
                for(y=y0;y>y1;y--)
                {
                    boundaryFill(x,floor(y+0.5),t);
                    y--;
                }
            }

        }

    }
    else //m>1
    {
        if(dx!=0)
        {
            x=x0;
            if(y1>=y0)
            {
                for(y=y0;y<y1;y++)
                {
                    boundaryFill(floor(x+0.5),y,t);
                    x+=(float)(1.0/m);
                }
            }
            else
            {
                for(y=y0;y>y1;y--)
                {
                    boundaryFill(floor(x+0.5),y,t);
                    x-=(float)(1.0/m);
                }
            }

        }
        else
        {
            x=x0;

            for(y=y0;y<y1;y++)
            {
                boundaryFill(floor(x+0.5),y,t);
                y++;

            }
        }

    }
}

void line::drawLine(int x0, int y0, int x1, int y1)
{
    double dx=x1-x0;
    double dy=y1-y0;

    double m= dy/dx;
    float y=y0;
    float x;

    if(m<=1)
    {
        if(dx!=0)
        {

            if(x1>=x0)
            {
                for(x=x0;x<x1;x+=1)
                {
                    boundaryFill(x,floor(y+0.5),t);
                    y+=m;
                }
            }
            else
            {
                for(x=x0;x>x1;x--)
                {
                    boundaryFill(x,floor(y+0.5),t);
                    y-=m;
                }
            }

        }
        else
        {
            x=x0;
            if(y1>=y0)
            {
                for(y=y0;y<y1;y++)
                {
                    boundaryFill(x,floor(y+0.5),t);
                    y++;
                }
            }
            else
            {
                for(y=y0;y>y1;y--)
                {
                    boundaryFill(x,floor(y+0.5),t);
                    y--;
                }
            }

        }

    }
    else //m>1
    {
        if(dx!=0)
        {
            x=x0;
            if(y1>=y0)
            {
                for(y=y0;y<y1;y++)
                {
                    boundaryFill(floor(x+0.5),y,t);
                    x+=(float)(1.0/m);
                }
            }
            else
            {
                for(y=y0;y>y1;y--)
                {
                    boundaryFill(floor(x+0.5),y,t);
                    x-=(float)(1.0/m);
                }
            }

        }
        else
        {
            x=x0;

            for(y=y0;y<y1;y++)
            {
                boundaryFill(floor(x+0.5),y,t);
                y++;

            }
        }

    }
}


void line::midPointLine()
{
    int x0=v1.getx();
    int x1=v2.getx();

    int y0=v1.gety();
    int y1=v2.gety();

    int dx=x1-x0;
    int dy=y1-y0;
    int d=2*dy-dx;
    int incE=2*dx;
    int incNE=2*(dy-dx);

    int x=x0;
    int y=y0;


    drawPixel2D(x,y);
    while(x<x1)
    {
        if(d<=0)
        {
            d+=incE;
        }
        else
        {
            d+=incNE;
            y++;
        }
        x++;
        drawPixel2D(x,y);
    }




}

void line::midPointLineAntialiasing()
{
    int x0=v1.getx();
    int x1=v2.getx();

    int y0=v1.gety();
    int y1=v2.gety();

    int dx=x1-x0;
    int dy=y1-y0;
    int d=2*dy-dx;
    int incE=2*dx;
    int incNE=2*(dy-dx);
    int two_v_dx=0;

    double invDenom=1.0/(2.0*sqrt(dx*dx+dy*dy));
    double two_dx_invDenom=2.0*dx*invDenom;


    int x=x0;
    int y=y0;

    primitives::intensifyPixel(x,y,0);
    primitives::intensifyPixel(x,y+1,two_dx_invDenom);
    primitives::intensifyPixel(x,y-1,two_dx_invDenom);
    drawPixel2D(x,y);


    while(x<x1)
    {
        if(d<=0)
        {
            two_v_dx=d+dx;
            d+=incE;
        }
        else
        {
            two_v_dx=d-dx;
            d+=incNE;
            y++;
        }
        x++;
        primitives::intensifyPixel(x,y,two_v_dx*invDenom);
        primitives::intensifyPixel(x,y+1,two_dx_invDenom-two_v_dx*invDenom);
        primitives::intensifyPixel(x,y-1,two_dx_invDenom+two_v_dx*invDenom);
        drawPixel2D(x,y);
    }

}

void line::Fill()
{
    int x0=v1.getx();
    int x1=v2.getx();

    int y0=v1.gety();
    int y1=v2.gety();


    double dx=x1-x0;
    double dy=y1-y0;

    double m= dy/dx;
    float y=y0;
    float x;

    if(m<=1)
    {
        if(dx!=0)
        {

            if(x1>=x0)
            {
                for(x=x0;x<x1;x+=1)
                {
                    thick1(x,floor(y+0.5),m,t);
                    y+=m;
                }
            }
            else
            {
                for(x=x0;x>x1;x--)
                {
                    thick1(x,floor(y+0.5),m,t);
                    y-=m;
                }
            }

        }
        else
        {
            x=x0;
            if(y1>=y0)
            {
                for(y=y0;y<y1;y++)
                {
                    thick1(x,floor(y+0.5),m,t);
                    y++;
                }
            }
            else
            {
                for(y=y0;y>y1;y--)
                {
                    thick1(x,floor(y+0.5),m,t);
                    y--;
                }
            }

        }

    }
    else //m>1
    {
        if(dx!=0)
        {
            x=x0;
            if(y1>=y0)
            {
                for(y=y0;y<y1;y++)
                {
                    thick1(floor(x+0.5),y,m,t);
                    x+=(float)(1.0/m);
                }
            }
            else
            {
                for(y=y0;y>y1;y--)
                {
                    thick1(floor(x+0.5),y,m,t);
                    x-=(float)(1.0/m);
                }
            }

        }
        else
        {
            x=x0;

            for(y=y0;y<y1;y++)
            {
                thick1(floor(x+0.5),y,m,t);
                y++;

            }
        }

    }


}

void line::Fill2()
{
    int x0=v1.getx();
    int x1=v2.getx();

    int y0=v1.gety();
    int y1=v2.gety();


    double dx=x1-x0;
    double dy=y1-y0;

    double m= dy/dx;
    float y=y0;
    float x;

    if(m<=1)
    {
        if(dx!=0)
        {

            if(x1>=x0)
            {
                for(x=x0;x<x1;x+=1)
                {
                    boundaryFill(x,floor(y+0.5),t);
                    y+=m;
                }
            }
            else
            {
                for(x=x0;x>x1;x--)
                {
                    boundaryFill(x,floor(y+0.5),t);
                    y-=m;
                }
            }

        }
        else
        {
            x=x0;
            if(y1>=y0)
            {
                for(y=y0;y<y1;y++)
                {
                    boundaryFill(x,floor(y+0.5),t);
                    y++;
                }
            }
            else
            {
                for(y=y0;y>y1;y--)
                {
                    boundaryFill(x,floor(y+0.5),t);
                    y--;
                }
            }

        }

    }
    else //m>1
    {
        if(dx!=0)
        {
            x=x0;
            if(y1>=y0)
            {
                for(y=y0;y<y1;y++)
                {
                    boundaryFill(floor(x+0.5),y,t);
                    x+=(float)(1.0/m);
                }
            }
            else
            {
                for(y=y0;y>y1;y--)
                {
                    boundaryFill(floor(x+0.5),y,t);
                    x-=(float)(1.0/m);
                }
            }

        }
        else
        {
            x=x0;

            for(y=y0;y<y1;y++)
            {
                boundaryFill(floor(x+0.5),y,t);
                y++;

            }
        }

    }
}

Circle::Circle()
{
    radius=1;
}

Circle::Circle(int r)
{
    this ->radius=r;
}

void Circle::setRadius(int r)
{
    this ->radius=r;
}

int Circle::getRadius()
{
    return radius;
}


void Circle::circlePoints(int x, int y)
{
    drawPixel2D(x,y);
    drawPixel2D(y,x);
    drawPixel2D(y,-x);
    drawPixel2D(x,-y);
    drawPixel2D(-x,-y);
    drawPixel2D(-y,-x);
    drawPixel2D(-y,x);
    drawPixel2D(-x,y);
}

void Circle::midPointCircle()
{
    int x=0;
    int y=radius;
    double d=5.0/4.0-radius;

    circlePoints(x,y);

    while(y>x)
    {
        if(d<0) //seleccionar E
            d+=2.0*x+3.0;
        else //seleccionar SE
        {
            d+=2.0*(x-y)+5.0;
            y--;
        }
        circlePoints(x,y);
        x++;
    }

}

void Circle::secondOCircle()
{
    int x=0;
    int y=radius;
    double d=1.0-radius;
    int de=3;
    int dse=-2*radius+5;

    circlePoints(x,y);
    while(y>x)
    {
        if(d<0) //seleccionar E
        {
            d+=de;
            de+=2;
            dse+=2;
        }
        else //seleccionar SE
        {
            d+=dse;
            de+=2;
            dse+=4;
            y--;
        }
        x++;
        circlePoints(x,y);
    }
}

void Ellipse::EllipsePoints(int x, int y)
{
    drawPixel2D(x,y);
    drawPixel2D(-x,y);
    drawPixel2D(-x,-y);
    drawPixel2D(x,-y);
}

Ellipse::Ellipse()
{
    this->a=0;
    this->b=0;
}

Ellipse::Ellipse(int a, int b)
{
    this->a=a;
    this->b=b;
}

void Ellipse::setAB(int a, int b)
{
    this->a=a;
    this->b=b;
}

void Ellipse::setA(int a)
{
    this->a=a;
}

void Ellipse::setB(int b)
{
    this->b=b;
}

int Ellipse::getA()
{
    return a;
}

int Ellipse::getB()
{
    return b;
}

void Ellipse::midPointEllipse()
{
    double d2;
    int x=0;
    int y=b;
    double d1=(b*b*(x+1)*(x+1)) + (a*a*(y-1/2)*(y-1/2))-a*a*b*b;

    EllipsePoints(x,y);
    //Gradiente de la region 1
    while(a*a*(y-0.5)>b*b*(x+1))
    {
        if(d1<0) //E
        {
            d1+=b*b*(2*x+3);
        }
        else
        {
            d1+=b*b*(2*x+3)+a*a*(-2*y+2);
            y--;
        }
        x++;
        EllipsePoints(x,y);
    }
    //Region 2
    d2=b*b + a*a*(-b+0.25);

    while(y>0)
    {
        if(d2<0) //SE
        {
            d2+=b*b*(2*x+4)+a*a*(-2*y+3);
            x++;
        }
        else //S
        {
            d2+=a*a*(-2*y+3);
        }
        y--;
        EllipsePoints(x,y);
    }
}




void Ellipse::fill()
{
    double d2;
    int x=0;
    int y=b;
    double d1=(b*b*(x+1)*(x+1)) + (a*a*(y-1/2)*(y-1/2))-a*a*b*b;

    drawLine(-x,y,x,y);
    drawLine(-x,-y,x,-y);
    //Gradiente de la region 1
    while(a*a*(y-0.5)>b*b*(x+1))
    {
        if(d1<0) //E
        {
            d1+=b*b*(2*x+3);
        }
        else
        {
            d1+=b*b*(2*x+3)+a*a*(-2*y+2);
            y--;
        }
        x++;
        drawLine(-x,y,x,y);
        drawLine(-x,-y,x,-y);
    }
    //Region 2
    d2=b*b + a*a*(-b+0.25);

    while(y>0)
    {
        if(d2<0) //SE
        {
            d2+=b*b*(2*x+4)+a*a*(-2*y+3);
            x++;
        }
        else //S
        {
            d2+=a*a*(-2*y+3);
        }
        y--;
        drawLine(-x,y,x,y);
        drawLine(-x,-y,x,-y);
    }

}

Rectangle::Rectangle()
{
    points.resize(4);

    fill=false;
}

Rectangle::Rectangle(point2D p1, point2D p2, point2D p3, point2D p4)
{
    points.resize(4);
    points[0]=p1;
    points[1]=p2;
    points[2]=p3;
    points[3]=p4;


    this->fill=false;
}

Rectangle::Rectangle(point2D p1, point2D p2, point2D p3, point2D p4, bool fill)
{
    points.resize(4);
    points[0]=p1;
    points[1]=p2;
    points[2]=p3;
    points[3]=p4;
    this->fill=fill;
}

void Rectangle::setP1(point2D p)
{
    points[0]=p;
}

void Rectangle::setP1(int x, int y)
{
    point2D p1;
    p1.setX(x);
    p1.setY(y);
    points[0]=p1;
}

void Rectangle::setP2(point2D p)
{
    points[1]=p;
}

void Rectangle::setP2(int x, int y)
{
    point2D p2;
    p2.setX(x);
    p2.setY(y);

    points[1]=p2;
}

void Rectangle::setP3(point2D p)
{
    points[2]=p;

}

void Rectangle::setP3(int x, int y)
{
    point2D p3;
    p3.setX(x);
    p3.setY(y);
    points[2]=p3;
}

void Rectangle::setP4(point2D p)
{
    points[3]=p;
}

void Rectangle::setP4(int x, int y)
{
    point2D p4;
    p4.setX(x);
    p4.setY(y);
    points[3]=p4;
}

void Rectangle::setFill(bool fill)
{
    this->fill=fill;
}

vector<point2D> Rectangle::getRectangle()
{
    return points;
}

point2D Rectangle::getP1()
{
    return points[0];
}

point2D Rectangle::getP2()
{
    return points[1];
}

point2D Rectangle::getP3()
{
    return points[2];
}

point2D Rectangle::getP4()
{
    return points[3];
}

bool Rectangle::getFillStatus()
{
    return fill;
}

void Rectangle::draw()
{
    unsigned int i;


    if(fill)
    {
        int xMin,yMin,xMax,yMax;

        xMin=points[0].getx();
        xMax=points[0].getx();

        yMin=points[0].gety();
        yMax=points[0].gety();

        for(i=0;i<points.size()-1;i++)
        {
            //Obteniendo xMin y xmax
            if(points[i].getx()<=xMin)
            {
                xMin=points[i].getx();
            }
            else if(points[i].getx()>=xMin)
            {
                xMax=points[i].getx();

            }
            //Obteniendo yMin y yMax
            if(points[i].gety()<=yMin)
            {
                yMin=points[i].gety();
            }
            else if(points[i].gety()>=yMin)
            {
                yMax=points[i].gety();

            }
        }


        for(int j=yMax;j>yMin;j--)
        {
            for(int k=xMin;k<xMax;k++)
            {
                drawPixel2D(k,j);
            }
        }







    }

    for(i=0;i<points.size()-1;i++)
    {
        drawLine(getRectangle().at(i).getx(),getRectangle().at(i).gety(),getRectangle().at(i+1).getx(),getRectangle().at(i+1).gety());
    }
    drawLine(getRectangle().at(i).getx(),getRectangle().at(i).gety(),getRectangle().at(0).getx(),getRectangle().at(0).gety());


}

Polygon::Polygon()
{
    fill=false;
}

void Polygon::setpoint(point2D p)
{
    points.push_back(p);
}

void Polygon::setpoint(int x, int y)
{
    point2D p;
    p.setpoint(x,y);
    points.push_back(p);
}

void Polygon::setFill(bool fill)
{
    this->fill=fill;
}

point2D Polygon::getPoint(int index)
{
    return points.at(index);
}

bool Polygon::getFillStatus()
{
    return fill;
}

void Polygon::draw()
{
    unsigned int i;

    if(fill)
    {
        polygonFill();
    }

    for(i=0;i<points.size()-1;i++)
    {
        drawLine(getPoint(i).getx(),getPoint(i).gety(),getPoint(i+1).getx(),getPoint(i+1).gety());
    }
    drawLine(getPoint(i).getx(),getPoint(i).gety(),getPoint(0).getx(),getPoint(0).gety());

}

void Polygon::polygonFill()
{
    unsigned int i,j;
    int xMin,yMin,xMax,yMax;
    line scan;
    vector<point2D> intersections;

    xMin=points[0].getx();
    xMax=points[0].getx();

    yMin=points[0].gety();
    yMax=points[0].gety();

    for(i=0;i<points.size()-1;i++)
    {
        //Obteniendo xMin y xmax
        if(points[i].getx()<=xMin)
        {
            xMin=points[i].getx();
        }
        else if(points[i].getx()>=xMin)
        {
            xMax=points[i].getx();

        }
        //Obteniendo yMin y yMax
        if(points[i].gety()<=yMin)
        {
            yMin=points[i].gety();
        }
        else if(points[i].gety()>=yMax)
        {
            yMax=points[i].gety();

        }
    }

    scan.setV1(xMin,yMax);
    scan.setV2(xMax,yMax);


    //Calculando intersecciones
    for(i=yMax;i>yMin;i--)
    {
        scan.setV1(xMin,i);
        scan.setV2(xMax,i);

        for(j=0;j<points.size()-1;j++)
        {

            if(primitives::intersectRect(scan,points.at(j),points.at(j+1)))
            {
                intersections.push_back(primitives::intersectHor(scan,points.at(j),points.at(j+1)));
            }
        }
        if(primitives::intersectRect(scan,points.at(j),points.at(0)))
        {
            intersections.push_back(primitives::intersectHor(scan,points.at(j),points.at(0)));
        }


        //sort
        sort(intersections.begin(),intersections.end(),primitives::condicion);
        unique(intersections.begin(),intersections.end(),primitives::uniqueTest);

        //draw
        for(j=0;j<intersections.size();j+=2)
        {
            drawLine(intersections[j].getx(),intersections[j].gety(),intersections[j+1].getx(),intersections[j+1].gety());
        }

        intersections.clear();

    }



}






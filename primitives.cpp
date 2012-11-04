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




























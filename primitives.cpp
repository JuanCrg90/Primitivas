#include "primitives.h"

primitives::primitives()
{
}

void point::drawPixel2D(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}


double point::filter(int distance)
{
    //0.5 ->desviación estandar pendiente calcular
    //return exp(-distance)/(2*0.5);
    return 0.5999+0.120*distance+0.6819*(distance*distance)+0.2824*(distance*distance*distance);
}



void point::intensifyPixel(int x, int y, double distance)
{
    double intensity=filter(distance);
    glColor3f(intensity,intensity,intensity);
}





void line::DrawLine(int x0, int y0, int x1, int y1)
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
            for(x=x0;x<x1;x+=1)
            {
                drawPixel2D(x,floor(y+0.5));
                y+=m;
            }
        }
        else
        {
            x=x0;
            for(y=y0;y<y1;y++)
            {
                drawPixel2D(x,floor(y+0.5));
                y++;

            }
        }

    }
    else //m>1
    {
        if(dx!=0)
        {
            x=x0;
            for(y=y0;y<y1;y++)
            {
                drawPixel2D(floor(x+0.5),y);
                x+=(float)(1.0/m);
            }
        }
        else
        {
            x=x0;
            for(y=y0;y<y1;y++)
            {
                drawPixel2D(round(x+0.5),y);
                y++;

            }
        }

    }


}

void line::midPointLine(int x0, int y0, int x1, int y1)
{
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

void line::midPointLineAntialiasing(int x0, int y0, int x1, int y1)
{


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

    intensifyPixel(x,y,0);
    intensifyPixel(x,y+1,two_dx_invDenom);
    intensifyPixel(x,y-1,two_dx_invDenom);
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
        intensifyPixel(x,y,two_v_dx*invDenom);
        intensifyPixel(x,y+1,two_dx_invDenom-two_v_dx*invDenom);
        intensifyPixel(x,y-1,two_dx_invDenom+two_v_dx*invDenom);
        drawPixel2D(x,y);
    }


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

    for(i=-t/2;i<t/2;i++)
    {
        for(j=-t/2;j<t/2;j++)
        {
            drawPixel2D(x+i,y+j);
        }
    }
}

void line::DrawLineFill(int x0, int y0, int x1, int y1, int t)
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
            for(x=x0;x<x1;x+=1)
            {
                thick1(x,floor(y+0.5),m,t);

                y+=m;
            }
        }
        else
        {
            x=x0;
            for(y=y0;y<y1;y++)
            {
                thick1(x,floor(y+0.5),m,t);
                y++;

            }
        }

    }
    else //m>1
    {
        if(dx!=0)
        {
            x=x0;
            for(y=y0;y<y1;y++)
            {
                thick1(floor(x+0.5),y,m,t);
                x+=(float)(1.0/m);
            }
        }
        else
        {
            x=x0;
            for(y=y0;y<y1;y++)
            {
                thick1(round(x+0.5),y,m,t);
                y++;

            }
        }

    }

}

void line::DrawLineFill2(int x0, int y0, int x1, int y1, int t)
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
            for(x=x0;x<x1;x+=1)
            {
                boundaryFill(x,floor(y+0.5),t);

                y+=m;
            }
        }
        else
        {
            x=x0;
            for(y=y0;y<y1;y++)
            {
                boundaryFill(x,floor(y+0.5),t);
                y++;

            }
        }

    }
    else //m>1
    {
        if(dx!=0)
        {
            x=x0;
            for(y=y0;y<y1;y++)
            {
                boundaryFill(floor(x+0.5),y,t);
                x+=(float)(1.0/m);
            }
        }
        else
        {
            x=x0;
            for(y=y0;y<y1;y++)
            {
                boundaryFill(round(x+0.5),y,t);
                y++;

            }
        }

    }

}

void ellipse::EllipsePoints(int x, int y)
{

    drawPixel2D(x,y);
    drawPixel2D(-x,y);
    drawPixel2D(-x,-y);
    drawPixel2D(x,-y);
}

void ellipse::midPointEllipse(int a, int b)
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

void circle::circlePoints(int x, int y)
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

void circle::midPointCircle(int radius)
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

void circle::secondOCircle(int radius)
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







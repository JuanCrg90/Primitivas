#include "glvisual.h"

glvisual::glvisual()
{
}


glvisual::~glvisual()
{

}


void glvisual::initializeGL()
{

    glShadeModel(GL_SMOOTH);
    qglClearColor(Qt::black);

    glClearDepth(1.0f);		// Depth Buffer Setup
    glDepthFunc(GL_LEQUAL); //Depth function
    glEnable(GL_DEPTH_TEST);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
}


void glvisual::resizeGL(int w, int h)
{
    width=w;
    height=h;

    //qDebug()<<width/2<<height/2;

    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f,width,0.0f,height,-1.0f,1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void glvisual::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    draw();
}

void glvisual::draw()
{


    Polygon p,cut;
    Rectangle r1;



    p.setpoint(100,300);
    p.setpoint(200,200);
    p.setpoint(300,300);
    p.setpoint(200,400);


    glColor3f(1.0,0.0,0.0);
    p.draw();



    r1.setP1(150,450);
    r1.setP2(150,50);
    r1.setP3(250,50);
    r1.setP4(250,450);
    glColor3f(1.0,0.0,1.0);
    r1.draw();

    cut=primitives::polygonClipping(p,r1);
    glColor3f(1.0,1.0,0.0);
    cut.setFill(true);
    cut.draw();


    /*


    line l(50,50,300,300);
    Rectangle r;

    r.setP1(120,120);
    r.setP2(280,120);
    r.setP3(280,280);
    r.setP4(120,280);

    glColor3f(1.0,1.0,1.0);
    r.draw();


    glPushMatrix();
    glColor3f(1.0,0.0,0.0);
    l.drawLine();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0,1.0,0.0);
    primitives::cohenSutherlandClippingLine(l.getV1().getx(),l.getV1().gety(),l.getv2().getx(),l.getv2().gety(),120,280,120,280);
    glPopMatrix();*/








}

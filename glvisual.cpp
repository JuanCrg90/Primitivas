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


    line l;
    Circle c;
    Ellipse e;
    l.setV1(100,100);
    l.setV2(-100,-200);

    glColor3f(1.0,0.0,0.0);
    l.setThick(10);
    l.drawLine();

    c.setRadius(50);
    glPushMatrix();
    glTranslatef(100,100,0);

    c.midPointCircle();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(300,300,0);
    e.setAB(50,100);
    e.midPointEllipse();
    glColor3f(0,1,0);
    e.fill();
    glPopMatrix();






}

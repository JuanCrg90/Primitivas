#include "glvisual.h"

glvisual::glvisual()
{
    point2D aux;

    srand(time(NULL));

    width=642;
    height=509;



    for(int i=0;i<NUM_POINTS;i++)
    {
        aux.setpoint(rand()%(int)width,rand()%(int)height);
        //aux.setpoint(110,300);
        myPoints.push_back(aux);

    }

    qTree.partition(myPoints,width,height);





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

    qDebug()<<width<<height;

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

    glColor3f(1.0,1.0,1.0);
    qTree.recorrer();

    glColor3f(1.0,0.0,0.0);
    glPointSize(1.0);
    for(int i=0;i<NUM_POINTS;i++)
    {
        myPoints.at(i).draw();

    }


}

#ifndef GLVISUAL_H
#define GLVISUAL_H

#include <QGLWidget>
#include <time.h>
#include "primitives.h"

#define NUM_POINTS 50

class glvisual : public QGLWidget
{
    Q_OBJECT
public:
    glvisual();
    ~glvisual();
    
signals:

    
public slots:
    void draw();


private:
    float width,height;
    void initializeGL();
    void resizeGL(int w,int h);
    void paintGL();
    vector <point2D> myPoints;


    QuadTree qTree;
    mytree<QuadNode> myQuadTree; //estructura del arbol






    
};

#endif // GLVISUAL_H

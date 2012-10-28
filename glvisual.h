#ifndef GLVISUAL_H
#define GLVISUAL_H

#include <QGLWidget>

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

    
};

#endif // GLVISUAL_H

#include <QApplication>
#include "mainwindow.h"

int main(int argc,char*argv[])
{
//Prueba
    QApplication app(argc,argv);
    MainWindow m;
    m.show();
    app.exec();

    return 0;
}



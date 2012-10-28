#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Convex Hull");

    q=new glvisual;

    ui->gridLayout_2->addWidget(q,0,0,1,1);

}

MainWindow::~MainWindow()
{
    delete ui;

}


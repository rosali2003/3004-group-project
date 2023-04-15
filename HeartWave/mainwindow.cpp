#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"

#include<QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QVector<double> x(101), y(101);
//    for(int i=0; i<101; ++i) {
//        x[i] = i/50.0 -1;
//        y[i] = x[i]*x[i];
//    }
//    ui->graph->addGraph();
//    ui->graph->graph(0)->setData(x,y);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ok_clicked()
{
    
}

void MainWindow::on_right_clicked()
{
    
}

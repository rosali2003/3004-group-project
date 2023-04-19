#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , device(new Device())
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

/* void MainWindow::on_power_clicked()
{
    if(device->togglePower()) {
        ui->blackScreen->setVisible(false);
        ui->listView->setModel(device->getModel());
        ui->listView->setCurrentIndex(device->getCurrScreen());
    } else {
        ui->blackScreen->setVisible(true);
    }
}

void MainWindow::on_up_clicked()
{
    ui->listView->setCurrentIndex(device->goUp());
}

void MainWindow::on_down_clicked()
{
    ui->listView->setCurrentIndex(device->goDown());
}*/

void MainWindow::on_power_clicked()
{
    if(device->togglePower()) {
        ui->blackScreen->setVisible(false);
        ui->listView->setModel(device->getModel());
        ui->listView->setCurrentIndex(device->getCurrScreen());
    } else {
        ui->blackScreen->setVisible(true);
    }
}

void MainWindow::on_up_clicked()
{
    ui->listView->setCurrentIndex(device->goUp());
}

void MainWindow::on_down_clicked()
{
    ui->listView->setCurrentIndex(device->goDown());
}

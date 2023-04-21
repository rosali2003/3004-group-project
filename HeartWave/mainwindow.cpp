#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>
#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , device(new Device())
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    device = new Device();
    dataTimer = new QTimer(this);
    heartRateIterator=0;
    coherenceIterator = 0;
//    MainWindow::displayGraph();

}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::on_ok_clicked(){}

//void MainWindow::on_right_clicked(){}

void MainWindow::displayGraph() {
    ui->graph->addGraph(); // blue line
    ui->graph->graph(0)->setPen(QPen(QColor(40, 110, 255)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->graph->xAxis->setTicker(timeTicker);
    ui->graph->axisRect()->setupFullAxesBox();
    ui->graph->yAxis->setRange(60, 150);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->graph->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->graph->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->graph->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->graph->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    device->calculateCoherenceScores();
    qDebug() << "coherence scores"<<device->getCoherenceScores();
    connect(dataTimer, &QTimer::timeout, this, &MainWindow::realTimeDataSlot);

    time = QTime::currentTime();
    dataTimer->start(0); // Interval 0 means to refresh as fast as possible
}

void MainWindow::realTimeDataSlot() {
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    static double lastBatteryDrainKey = 0;
    static double coherenceKey = 0;

    if (key-lastPointKey > 1) // at most add point every 2 ms
    {
     // qDebug() << "time elapsed: " << key;
      ui->graph->graph(0)->addData(key, device->getHRvalues().at(heartRateIterator%NUMHR));
      ++heartRateIterator;

      // rescale value (vertical) axis to fit the current data:
      ui->graph->graph(0)->rescaleValueAxis();

      lastPointKey = key;
   }

    // If 4 seconds have gone by without draining battery
    if (key-lastBatteryDrainKey >= 4){
        //qDebug() << "Battery percentage: " << device->decreaseBattery(1); // decrease by 1% every 4 seconds = 6-7 minute total session runtime
        lastBatteryDrainKey = key;
    }

    if(key-coherenceKey > 5) {
        this->displayCoherenceValues();
        coherenceKey = key;
     }

    // make key axis range scroll with the data (at a constant range size of 8):
    ui->graph->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->graph->replot();

}

void MainWindow::displayCoherenceValues() {
    QString score = "";
    score = QString::number(device->getCoherenceScores().at(coherenceIterator), 'f', 2);
    ++coherenceIterator;
    ui->coherence_value->setText(score);

}

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

void MainWindow::on_ok_clicked()
{
    if(device->isMainMenu()) {
        ui->listView->setModel(device->setModel());
        ui->listView->setCurrentIndex(device->getCurrScreen());
        if (ui->listView->model() == nullptr) {
            //begin session clicked
            qDebug() << "begin session clicked";
            ui->listView->setVisible(false);
        }
    }
}

void MainWindow::on_menu_clicked()
{
    qDebug() << "menu button clicked";
    ui->listView->setVisible(true);
    ui->listView->setModel(device->goToMenu());
    ui->listView->setCurrentIndex(device->getCurrScreen());
}

void MainWindow::beginSession(){
    displayGraph();
}

void MainWindow::endSession(){
    dataTimer->stop();
}

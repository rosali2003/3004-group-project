#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>
#include <QDebug>



using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    device = new Device();

    dataTimer = new QTimer(this);
    dataTimer->start(1000);
    i=0;
    coherenceIterator = 0;
    MainWindow::displayGraph();

}

MainWindow::~MainWindow()
{
    delete ui;
}

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
    connect(dataTimer, &QTimer::timeout, this, &MainWindow::realTimeDataSlot);
    time = QTime::currentTime();
    dataTimer->start(0); // Interval 0 means to refresh as fast as possible

}

void MainWindow::realTimeDataSlot() {
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds

    static double lastPointKey = 0;
    static double coherenceKey = 0;

        if (key-lastPointKey > 1) // at most add point every 1 sec
        {
            ui->graph->graph(0)->addData(key, device->getHRvalues().at(i%NUMHR));
            ++i;
          // rescale value (vertical) axis to fit the current data:
            if(key-coherenceKey > 5) {
                this->displayCoherenceValues();
                coherenceKey = key;
             }

          ui->graph->graph(0)->rescaleValueAxis();
          lastPointKey = key;
        }


    // make key axis range scroll with the data (at a constant range size of 8):
    ui->graph->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->graph->replot();
}

void MainWindow::displayCoherenceValues() {
    QString score = "";
    score = QString::number(device->getCoherenceScores().at(coherenceIterator));
    ++coherenceIterator;
    ui->coherence_value->setText(score);

}


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
    device->calculateCoherenceScores();
    ui->battery->setValue(device->getBatteryLevel());
    dataTimer = new QTimer(this);
    heartRateIterator=0;
    coherenceIterator = 0;



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
    qDebug() << "coherence scores"<<device->getCoherenceScores();
    connect(dataTimer, &QTimer::timeout, this, &MainWindow::realTimeDataSlot);

    achievement_score = 0;
    time = QTime::currentTime();
    date = QDateTime::currentDateTime();
    dataTimer->start(100); // Interval 0 means to refresh as fast as possible
}

void MainWindow::realTimeDataSlot() {
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    displayDruation();
    static double lastPointKey = 0;
    static double lastBatteryDrainKey = 0;
    static double coherenceKey = 0;

    if (key-lastPointKey >= 1) // at most add point ever
    {
      qDebug() << "time elapsed: " << key;
      ui->graph->graph(0)->addData(key, device->getHRvalues().at(heartRateIterator%NUMHR));
      ++heartRateIterator;

      // rescale value (vertical) axis to fit the current data:
      ui->graph->graph(0)->rescaleValueAxis();

      lastPointKey = key;
   }

    // If 4 seconds have gone by without draining battery
    if (key-lastBatteryDrainKey >= 4){
        // decrease by 1% every 4 seconds = 6-7 minute total session runtime
        ui->battery->setValue(device->decreaseBattery(1));
        lastBatteryDrainKey = key;
    }

    if(key-coherenceKey >= 5) {
        this->displayCoherenceValues();
        coherenceKey = key;
     }

    // make key axis range scroll with the data (at a constant range size of 8):
    ui->graph->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->graph->replot();
}

void MainWindow::displayCoherenceValues() {
    float coherence_score = device->getCoherenceScores().at(coherenceIterator%30);
    achievement_score += coherence_score;
    QString score = "";
    score = QString::number(coherence_score, 'f', 2);
    ++coherenceIterator;
    ui->coherence_value->setText(score);
    ui->achievement_value->setText(QString::number(achievement_score, 'f', 2));
}

void MainWindow::displayDruation() {
    QString duration = "";
    duration = QString::number(time.elapsed()/1000.0, 'f', 2);
    duration += "s";
    ui->length_value->setText(duration);
}

void MainWindow::on_power_clicked()
{
    if(device->togglePower()) {
        // power on
        ui->battery->setValue(device->getBatteryLevel());
        ui->blackScreen->setVisible(false);
        ui->listView->setModel(device->getModel());
        ui->listView->setCurrentIndex(device->getCurrScreen());
    } else {
        // power off
        endSession(); //end session if was running
        ui->blackScreen->setVisible(true);

        // go to menu if not already for next boot up
        ui->listView->setVisible(true);
        ui->listView->setModel(device->goToMenu());
        ui->listView->setCurrentIndex(device->getCurrScreen());
    }
}

void MainWindow::on_up_clicked()
{
    if (device->isOn()){
       ui->listView->setCurrentIndex(device->goUp());
    }
}

void MainWindow::on_down_clicked()
{
    if (device->isOn()){
       ui->listView->setCurrentIndex(device->goDown());
    }
}

void MainWindow::on_ok_clicked()
{
    if(device->isOn() && device->isMainMenu()) {
        ui->listView->setModel(device->setModel());
        ui->listView->setCurrentIndex(device->getCurrScreen());
        if (ui->listView->model() == nullptr) {
            //begin session clicked
            qDebug() << "begin session clicked";
            beginSession();
            ui->listView->setVisible(false);
        }
    }
}

void MainWindow::on_menu_clicked()
{
    if (device->isOn()){
        endSession();
        ui->listView->setVisible(true);
        ui->listView->setModel(device->goToMenu());
        ui->listView->setCurrentIndex(device->getCurrScreen());
    }
}

void MainWindow::beginSession(){
    if (device->isOn()){
      displayGraph();
    }
}

void MainWindow::endSession(){
    if (dataTimer->isActive()){
        dataTimer->stop();
        float duration = time.elapsed()/1000.0;
        float c = coherenceIterator%30;
        float avg_score = 0;
        QVector<float> list = device->getCoherenceScores();
        for(int i = 0; i < c; i++){
            avg_score += list.at(i);
        }
        // date and time member variables are updated at the start of every session
        device->addSessionToHistory(date, duration, avg_score/c, achievement_score);
        device->updateHistory();
        ui->coherence_value->setText("0.0");
        ui->length_value->setText("00.00");
        ui->achievement_value->setText("0.0");
    }
}

void MainWindow::on_back_clicked()
{
    if(device->isOn()){
        endSession();
        ui->listView->setVisible(true);
        ui->listView->setModel(device->goToMenu());
        ui->listView->setCurrentIndex(device->getCurrScreen());
    }
}

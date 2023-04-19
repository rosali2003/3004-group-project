#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "device.h"
#include <QTimer>
#include <QDateTime>
#include "qcustomplot.h"
#include <QTime>
<<<<<<< HEAD
=======
<<<<<<< HEAD
#include "HeartDB.h"
=======



>>>>>>> trying to display and calculate coherence values, not working
>>>>>>> trying to display and calculate coherence values, not working

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void realTimeDataSlot();
    void displayCoherenceValues();

    void on_power_clicked();

    void on_up_clicked();

    void on_down_clicked();

    void on_ok_clicked();
    
    void on_right_clicked();
    
    
private:
    Ui::MainWindow *ui;
    Device *device;
    QTimer *dataTimer;
<<<<<<< HEAD
=======
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> trying to display and calculate coherence values, not working
    int heartRateIterator;
    QTime time;
    void displayGraph();
    HeartDB heartDB;
<<<<<<< HEAD
=======
    
=======
    int i;
>>>>>>> --amend
=======
    static QTime time(QTime::currentTime());
    int i;
    int coherenceIterator = 0;
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    double lastPointKey = 0;
>>>>>>> trying to display and calculate coherence values, not working
>>>>>>> trying to display and calculate coherence values, not working
};
#endif // MAINWINDOW_H

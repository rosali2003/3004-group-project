#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
<<<<<<< HEAD
=======
#include "HeartDB.h"
>>>>>>> Using timer for battery
#include "device.h"
#include <QTimer>
#include <QDateTime>
#include "qcustomplot.h"
<<<<<<< HEAD
#include <QTime>
#include "HeartDB.h"
=======
>>>>>>> Using timer for battery

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
    int heartRateIterator;
    QTime time;
    void displayGraph();
=======
    QTime time;
>>>>>>> Using timer for battery
    int i;
};
#endif // MAINWINDOW_H

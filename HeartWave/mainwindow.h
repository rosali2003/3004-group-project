#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "device.h"
#include <QTimer>
#include <QDateTime>
#include "qcustomplot.h"
#include <QTime>
#include "HeartDB.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     void displayCoherenceValues();
private slots:
    void realTimeDataSlot();

    void on_power_clicked();

    void on_up_clicked();

    void on_down_clicked();
    
    void on_ok_clicked();

    void on_menu_clicked();

    void on_back_clicked();

private:
    Ui::MainWindow *ui;
    Device *device;
    QTimer *dataTimer;
    int heartRateIterator;
    float achievement_score;
    QDateTime date;
    QTime time;
    void displayGraph();
    HeartDB heartDB;
    int coherenceIterator;
    void beginSession();
    void endSession();
    void displayDruation();
};
#endif // MAINWINDOW_H

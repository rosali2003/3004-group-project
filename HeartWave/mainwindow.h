#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "device.h"
#include <QTimer>
#include <QDateTime>
#include "qcustomplot.h"
#include <QTime>




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
    void displayGraph();
    void realTimeDataSlot();
    void displayCoherenceValues();

private:
    Ui::MainWindow *ui;
    Device *device;
    QTimer *dataTimer;
    static QTime time(QTime::currentTime());
    int i;
    int coherenceIterator = 0;
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    double lastPointKey = 0;
};
#endif // MAINWINDOW_H

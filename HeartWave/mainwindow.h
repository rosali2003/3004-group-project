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
     void displayCoherenceValues();
private slots:
    void displayGraph();
    void realTimeDataSlot();

private:
    Ui::MainWindow *ui;
    Device *device;
    QTimer *dataTimer;
    QTime time;
    int i;
    int coherenceIterator;
};
#endif // MAINWINDOW_H

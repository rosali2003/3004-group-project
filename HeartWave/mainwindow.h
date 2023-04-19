#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "device.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //void displayGraph();

private slots:
    void on_power_clicked();

    void on_up_clicked();

    void on_down_clicked();

private:
    Ui::MainWindow *ui;
    Device* device;
};
#endif // MAINWINDOW_H

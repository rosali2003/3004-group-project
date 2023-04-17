#ifndef DEVICE_H
#define DEVICE_H
#include <QTimer>
#include <QDateTime>
#include "battery.h"
#include "display.h"
#include <QList>
#include <stdio.h>
#include <QVector>
#include "defs.h"
#include "qcustomplot.h"


class Device{
public:
    Device();
    bool tooglePower();
    bool beginSession();
    bool quitSesson();
    bool addSessionToHistory();
    bool chargeBattery();
    int descreaseBattery(int step);
    View* goUp();
    View* goDown();
    View* handleOK();
    View* goToMain();
    View* goBack();
    void displayheartRate();
    void displayCoherenceScores();
    QVector<int>& getHRvalues();
private:
    QTimer *timer;
    Display display;
    Battery battery;
    bool hrContact;
    QList<int> programs;
    bool powerOn;
    int batteryPercentage;
    bool programRunning;
    QVector<int> HRvalues;
    QVector<int> coherenceValues;
};

#endif // DEVICE_H

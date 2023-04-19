#ifndef DEVICE_H
#define DEVICE_H

#include <QTimer>
#include <QDateTime>
#include "battery.h"
#include "display.h"
#include "HeartDB.h"
#include <QList>
#include <stdio.h>
#include <QVector>
#include "defs.h"
#include "qcustomplot.h"
#include "HeartDB.h"


class Device {
public:
    // constructors
    Device();

    // getters
    QStringListModel* getModel();
    QModelIndex getCurrScreen();

    // others
    bool togglePower();
    bool beginSession();
    bool quitSesson();
    bool addSessionToHistory(QDateTime date, int duration, float avg_coherence);
    bool chargeBattery();
<<<<<<< HEAD
    int descreaseBattery(int step);
    QModelIndex goUp();
    QModelIndex goDown();
=======
    int decreaseBattery(int step);
    View* goUp();
    View* goDown();
>>>>>>> Using timer for battery
    View* handleOK();
    View* goToMain();
    View* goBack();
    void displayheartRate();
    void displayCoherenceScores();
    QVector<int>& getHRvalues();
private:
    HeartDB* db;
    QTimer *timer;
    Display display;
<<<<<<< HEAD
    Battery battery;

private:
    QTimer timer;
    Display *display;
=======
>>>>>>> Using timer for battery
    Battery *battery;
    bool hrContact;
    QStringListModel *screens;
    bool powerOn;
    int batteryPercentage;
    bool programRunning;
    QVector<int> HRvalues;
    QVector<int> coherenceValues;
    HeartDB *database;
};

#endif // DEVICE_H

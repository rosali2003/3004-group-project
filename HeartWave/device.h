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
#include <cmath>
#include <iostream>
//#include <string>



class Device {
public:
    // constructors
    Device();

    // setters
    QStringListModel* setModel();

    // getters
    QStringListModel* getModel();
    QModelIndex getCurrScreen();

    // others
    bool togglePower();
    bool beginSession();
    bool quitSesson();
    bool addSessionToHistory(QDateTime date, int duration, float avg_coherence);
    bool chargeBattery();
    int decreaseBattery(int step);
    QModelIndex goUp();
    QModelIndex goDown();
    QStringListModel* goToMenu();
    void deleteHistory();
    bool isMainMenu();
    void displayheartRate();
    void displayCoherenceScores();
    QVector<int>& getHRvalues();
    QVector<float>& getCoherenceScores();
    void calculateCoherenceScores();

private:
    QTimer *timer;
    Display *display;
    Battery *battery;
    bool hrContact;
    QStringListModel *screens;
    bool powerOn;
    int batteryPercentage;
    bool programRunning;
    QVector<int> HRvalues;
    QVector<float> coherenceValues;
    HeartDB *database;
    bool deleteSessions();
    QVector<SessionRecord*> getSessions();
};

#endif // DEVICE_H

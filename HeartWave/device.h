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

class Device {
public:
    // constructors
    Device();

    // setters
    QStringListModel* setModel();

    // getters
    QStringListModel* getModel();
    QModelIndex getCurrScreen();
    QVector<int>& getHRvalues();
    QVector<float>& getCoherenceScores();

    // others
    bool togglePower();
    bool addSessionToHistory(QDateTime date, float duration, float avg_coherence, float achievement_score);
    bool chargeBattery();
    int decreaseBattery(int step);
    QModelIndex goUp();
    QModelIndex goDown();
    QStringListModel* goToMenu();
    QStringListModel* goToSummary() {return display->goToSummary();}
    void deleteHistory();
    bool isMainMenu();
    void calculateCoherenceScores();
    bool isOn(){return powerOn;}
    void updateHistory();
    int getBatteryLevel(){return battery->getBatteryPercentage();}
    void updateProfile(int battery){database->updateProfile(battery);}
    bool deleteSession(int index) {return database->deleteSession(index);}

private:
    Display *display;
    Battery *battery;
    QStringListModel *screens;
    bool powerOn;
    QVector<int> HRvalues;
    QVector<float> coherenceValues;
    HeartDB *database;
    bool deleteSessions();
    QVector<SessionRecord*> getSessions();
};

#endif // DEVICE_H

#ifndef DEVICE_H
#define DEVICE_H
#include <QTimer>
#include "battery.h"
#include "display.h"
#include "HeartDB.h"
#include <QList>


class Device{
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
    int descreaseBattery(int step);
    QModelIndex goUp();
    QModelIndex goDown();
    QStringListModel* goToMenu();
    void deleteHistory();
    bool isMainMenu();

private:
    QTimer timer;
    Display *display;
    Battery *battery;
    bool hrContact;
    QStringListModel *screens;
    bool powerOn;
    int batteryPercentage;
    bool programRunning;
    HeartDB *database;
};

#endif // DEVICE_H

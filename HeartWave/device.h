#ifndef DEVICE_H
#define DEVICE_H
#include <QTimer>
#include "battery.h"
#include "display.h"
#include <QList>


class Device{
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
    bool addSessionToHistory();
    bool chargeBattery();
    int descreaseBattery(int step);
    QModelIndex goUp();
    QModelIndex goDown();
    View* handleOK();
    View* goToMain();
    View* goBack();

private:
    QTimer timer;
    Display *display;
    Battery *battery;
    bool hrContact;
    QStringListModel *screens;
    bool powerOn;
    int batteryPercentage;
    bool programRunning;
};

#endif // DEVICE_H

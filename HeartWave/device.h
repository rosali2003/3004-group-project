#ifndef DEVICE_H
#define DEVICE_H
#include <QTimer>
#include "battery.h"
#include "display.h"
#include <QList>


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
private:
    QTimer timer;
    Display display;
    Battery battery;
    bool hrContact;
    QList<int> programs;
    bool powerOn;
    int batteryPercentage;
    bool programRunning;
};

#endif // DEVICE_H

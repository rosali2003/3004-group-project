#include "device.h"
#include <iostream>

<<<<<<< HEAD
using namespace std;

// constructors
Device::Device()
{
    for(int i =0; i<NUMHR;i++) {
        HRvalues.push_back(HR[i]);
    }

}

<<<<<<< HEAD
    powerOn = false;
    display = new Display();
    database = new HeartDB();


QVector<int>& Device::getHRvalues(){
    return HRvalues;
}

// getters
QStringListModel* Device::getModel() {return display->getModel();}
QModelIndex Device::getCurrScreen() {return display->getCurrScreen();}

// others
QModelIndex Device::goUp() {
    return display->goUp();
}

QModelIndex Device::goDown() {
    return display->goDown();
}

bool Device::togglePower() {
    powerOn = !powerOn;
    return powerOn;
}

bool Device::addSessionToHistory(QDateTime date, int duration, float avg_coherence) {
    SessionRecord *newSession = new SessionRecord(date, duration, avg_coherence);

    return database->addSessionRecord(newSession);
=======
=======
>>>>>>> Using timer for battery
Device::Device() {
    db = new HeartDB();

    int battery_lvl = db->getBatteryLevel();
    battery = new Battery(battery_lvl);

<<<<<<< HEAD
int Device::decreaseBattery(int step) {
    return battery.decreaseBattery(int step);
>>>>>>> fix
=======
    for(int i =0; i<NUMHR;i++) {
        HRvalues.push_back(HR[i]);
//        cout << "Hr values at i " << " i " << i << " hrvalue " <<HRvalues.at(i) << endl;
    }
}

bool Device::chargeBattery() {
    return battery->chargeBattery();
}

int Device::decreaseBattery(int step) {
    return battery->decreaseBattery(step);
}

QVector<int>& Device::getHRvalues(){
    return HRvalues;
>>>>>>> Using timer for battery
}

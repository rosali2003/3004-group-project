#include "device.h"

// constructors
Device::Device()
{
    powerOn = false;
    display = new Display();
    database = new HeartDB();

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
}

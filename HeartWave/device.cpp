#include "device.h"

// constructors
Device::Device()
{
    powerOn = false;
    display = new Display();
    database = new HeartDB();

}

// setters
QStringListModel* Device::setModel() {
    return display->setModel();
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

void Device::deleteHistory() {
    database->deleteSessions();
}

bool Device::addSessionToHistory(QDateTime date, int duration, float avg_coherence) {
    SessionRecord session(date, duration, avg_coherence);
    return database->addSessionRecord(session);
}

QStringListModel* Device::goToMenu() {
    return display->goToMenu();
}

bool Device::isMainMenu() {
    return display->isMainMenu();
}

#include "device.h"

// constructors
Device::Device()
{
    powerOn = false;
    display = new Display();
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

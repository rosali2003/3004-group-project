#include "device.h"

using namespace std;

// constructors
Device::Device()
{
    for(int i =0; i<NUMHR;i++) {
        HRvalues.push_back(HR[i]);
    }

    powerOn = false;
    display = new Display();
    database = new HeartDB();
    battery = new Battery(database->getBatteryLevel());
    calculateCoherenceScores();

    foreach (float num, coherenceValues) {
        qDebug() << "coherence score: " << num;
    }

}

// setters
QStringListModel* Device::setModel() {
    return display->setModel();
}

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

void Device::deleteHistory() {
    database->deleteSessions();
}

bool Device::addSessionToHistory(QDateTime date, float duration, float avg_coherence, float achievement_score) {
    SessionRecord session(date, duration, avg_coherence, achievement_score);
    return database->addSessionRecord(session);
}

QStringListModel* Device::goToMenu() {
    return display->goToMenu();
}

bool Device::isMainMenu() {
    return display->isMainMenu();
}

QVector<SessionRecord*> Device::getSessions(){
    return database->getSessions();
}

bool Device::deleteSessions(){
    return database->deleteSessions();
}


bool Device::chargeBattery() {
    return battery->chargeBattery();
}

int Device::decreaseBattery(int step) {
    return battery->decreaseBattery(step);
}


QVector<float>& Device::getCoherenceScores(){
    return coherenceValues;
}

void Device::calculateCoherenceScores() {
    float largest =0;
    float smallest =200;
    for(int i=0; i<NUMHR;i++) {
        if(HRvalues.at(i) > largest) {
            largest = HRvalues.at(i);
        } else if(HRvalues.at(i) < smallest) {
            smallest = HRvalues.at(i);
        }

        if((i+1)%5 == 0) {
            coherenceValues.push_back((largest-smallest)/6);
            largest = 0;
            smallest = 200;
        }
    }

void Device::updateHistory(){
    display->updateHistory();
}

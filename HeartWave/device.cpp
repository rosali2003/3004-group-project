#include "device.h"
#include <iostream>

using namespace std;

// constructors
Device::Device()
{
    for(int i =0; i<NUMHR;i++) {
        HRvalues.push_back(HR[i]);
    }

}

    powerOn = false;
    display = new Display();
    database = new HeartDB();


QVector<int>& Device::getHRvalues(){
    return HRvalues;
}

QVector<int>& Device::getCoherenceScores(){
    return coherenceValues;
}

void Device::calculateCoherenceScores() {
    int largest =0;
    int smallest =0;
    for(int i=0; i<NUMHR;i++) {
        if(HRvalues.at(i) > largest) {
            largest = HRvalues.at(i);
        } else if(HRvalues.at(i) < smallest) {
            smallest = HRvalues.at(i);
        }

        if((i+1)%5 == 0) {
            coherenceValues.push_back(largest-smallest);
            largest = 0;
            smallest = 0;
        }
    }

    for(int i; i<30;i++){
        cout << "coherence values at i" << i<< " : " << coherenceValues.at(i) << endl;
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

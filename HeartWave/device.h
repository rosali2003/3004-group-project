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

/* Class Purpose: oversees all subclasses and acts as a control class taking input from MainWindow
 *
 * Data Members:
 * - Display *display: a pointer to the display object
 * - Battery *battery: a pointer to the battery object
 * - bool powerOn: keeps track of whether the device is powered on or not
 * - QVector<int> HRvalues: stores all of the heart rate values for when a session has begun
 * - QVector<float> coherenceValues: stores all of the coherence values for when a session has begun
 * - HeartDB *database: a pointer to the database to perform various actions based on UI input
 *
 * Class Functions:
 * - bool togglePower(): turns the device's power the opposite of what it is currently
 * - bool addSessionToHistory(QDateTime, float, float, float): add a completed session to the database with the given content
 * - bool chargeBattery(): calls the chargeBattery function in the battery class
 * - bool decreaseBattery(int): calls the decreaseBattery function in the battery class
 * - QModelIndex goUp(): class the goUp function in the display class
 * - QModelIndex goDown(): calls the goDown function in the display class
 * - QStringListModel* goToMenu(): calls the goToMenu function in the display class
 * - QStringListModel* goToSummary(): calls the goToSummary function in the display class
 * - void deleteHistory(): calls the deleteSessions function in the HeartDB class
 * - bool isMainMenu(): calls the isMainMenu function in the display class
 * - void calculateCoherenceScores(): runs the algorithm to calculate the coherence scores for during a session
 * - bool isOn(): returns whether the device is powered on or not
 * - void updateHistory(): calls the updateHistory function in the display class
 * - int getBatteryLevel(): calls the getBatteryPercentage function in the battery class
 * - void updateProfile(int): calls the updateProfile function in the database class
 * - bool deleteSession(int): calls the deleteSession function in the database class
 * - int updateBreathPacerValue(bool, int): updates the value of the breath pacer based on whether it is supposed to be increasing or decreasing
 * - bool updateBreathPacerDirection(bool, int): checks whether the pacer is empty or full and switches the direction
 * - int updateBreathPacerInterval(int, int): increases the value between breaths
 * - bool deleteSessions(): deletes all past sessions from the database
 * - QVector<SessionRecord*> getSessions(): calls the getSessions function in the database class
 */

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
    int updateBreathPacerValue(bool increasing, int breathPacerValue);
    bool updateBreathPacerDirection(bool increasing, int breathPacerValue);
    int updateBreathPacerInterval(int breathPacerValue, int breathPacerInterval);

private:
    Display *display;
    Battery *battery;
    bool powerOn;
    QVector<int> HRvalues;
    QVector<float> coherenceValues;
    HeartDB *database;
    bool deleteSessions();
    QVector<SessionRecord*> getSessions();
};

#endif // DEVICE_H

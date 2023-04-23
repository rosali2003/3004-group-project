#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "device.h"
#include <QTimer>
#include <QDateTime>
#include "qcustomplot.h"
#include <QTime>
#include "HeartDB.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/* Class Purpose: The main window of the application
 *
 * Data Members:
 * - Ui::MainWindow *ui: Pointer allowing making updates to ui
 * - Device *device: pointer to the control device through which the other classes are accessed
 * - QTimer *dataTimer, *breathPacer: Timers to synchronize events whilst session is active and breath pacer running.
 * - int heartRateIterator: Integer to keep track of the heart rate value in (int HR[]) in defs.h
 * - float achievement_score: Keeps track of achievement score whilst session active, updated every 5s, facilitated via dataTimer
 * - QDateTime date: Keeps track of date when session started to be stored in database
 * - QTime time: Keep track of time when session started, used when dataTimer times out to figure out session elapsed time
 * - HeartDB heartDB: Database manager to perform operations in database specified by HeartDB.h
 * - int coherenceIterator: Keeps track of coherence score in Device's coherenceValues Vector
 * - double lastPointKey: Key used in slot when timer times out which holds the time when the graph was last updated.
 * - double lastBatteryDrainKey: Key used in slot when timer times out which holds the time when the battery was last drained.
 * - double coherenceKey: Key used in slot when timer times out which holds the time when the coherence score was last updated.
 * - int breathPacerValue: Value to set UI breathPacer bar
 * - int breathPacerInterval: Value which holds interval to update breathPacer timer
 * - bool increasing: Boolean indicating wether breathPacer bar is currently increasing or not.
 *
 * Class Functions:
 * - void beginSession(): Begins session if device is turned on
 * - void endSession(): Ends session if session was active, saving session record to database and updating device's session history
 * - void displayDruation(): Display current session duration in seconds, facilitated by dataTimer
 * - void signalLowCoherence(): Update UI to turn on Red Coherence Indicator when low coherence during session
 * - void signalMediumCoherence(): Update UI to turn on Blue Coherence Indicator when medium coherence during session
 * - void signalHighCoherence(): Update UI to turn on Green Coherence Indicator when high coherence during session
 * - void resetCoherenceIndicators(): Resets all UI coherence indicators, scores, session duration, achievement score
 * - void resetBreathPacer(): Resetse breath pacer timer and UI
 * - void displayCoherenceValues(): Displays coherence values in UI when session active
 * - void displayGraph(): Initial function called when session starts, setting up variables and starting dataTimer and breathPacer
 *
 * Slots:
 * void realTimeDataSlot(): Slot called when dataTimer times out whilst session is running. Updates UI, battery, graph, and scores.
 * void on_power_clicked(): Slot handling when device power button clicked.
 * void on_up_clicked(): Slot handling when device up button clicked. For navigating menu and history tab.
 * void on_down_clicked(): Slot handling when device down button clicked. For navigating menu and history tab.
 * void on_ok_clicked(): Slot handling when device Ok button clicked. For starting session, seeing history, and/or deleting session in history.
 * void on_menu_clicked(): For ending session and returning to menu from History/Session.
 * void on_back_clicked(): For ending session and returning to menu from History/Session.
 * void on_recharge_button_clicked(): To recharge battery to 100%.
 * void on_delete_sessions_button_clicked(): To delete all sessions stored in database and update device history.
 * void on_hr_contact_checkbox_stateChanged(int arg1): To handle when HR checkbox state changes. Non-Zero value for arg1 signifies checkbox is checked.
 * void updateBreathPacer(): Updates breath pacer value, interval and UI
 *
 * Signals:
 * void batteryDrained(): Signal to be emitted when battery reaches 0% during session. It then calls on_power_clicked() slot to end session, saving it to database, and power off device.
 *
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
     void batteryDrained();
private slots:
    void realTimeDataSlot();

    void on_power_clicked();

    void on_up_clicked();

    void on_down_clicked();
    
    void on_ok_clicked();

    void on_menu_clicked();

    void on_back_clicked();

    void on_recharge_button_clicked();

    void on_delete_sessions_button_clicked();

    void on_hr_contact_checkbox_stateChanged(int arg1);

    void updateBreathPacer();
    
private:
    Ui::MainWindow *ui;
    Device *device;
    QTimer *dataTimer, *breathPacer;
    int heartRateIterator;
    float achievement_score;
    QDateTime date;
    QTime time;
    void displayGraph();
    HeartDB heartDB;
    int coherenceIterator;
    void beginSession();
    void endSession();
    void displayDruation();
    void signalLowCoherence();
    void signalMediumCoherence();
    void signalHighCoherence();
    void resetCoherenceIndicators();
    void resetBreathPacer();
    void displayCoherenceValues();
    double lastPointKey, lastBatteryDrainKey, coherenceKey;
    int breathPacerValue, breathPacerInterval;
    bool increasing;
};
#endif // MAINWINDOW_H

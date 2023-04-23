#ifndef BATTERY_H
#define BATTERY_H

/* Class Purpose: to keep track of current state of battery and handle manipulation of the battery
 *
 * Data Members:
 * - int batteryPercentage: keeps track of current battery charge
 *
 * Class Functions
 * - int decreaseBattery(int): decreases the battery percentage by the step indicated in the parameter
 * - bool chargeBattery(): sets the battery percentage back to 100%
 * - int getBatteryPercentage(): returns the current battery percentage
 */

class Battery {
public:
    Battery(int percent);
    int decreaseBattery(int step);
    bool chargeBattery();
    int getBatteryPercentage();
private:
    int batteryPercentage;
};

#endif // BATTERY_H

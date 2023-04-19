#ifndef BATTERY_H
#define BATTERY_H


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

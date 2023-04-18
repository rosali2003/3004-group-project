#ifndef BATTERY_H
#define BATTERY_H


class Battery {
public:
    Battery();
    int decreaseBattery(int step);
    bool chargeBattery();
private:
    int batteryPercentage;
};

#endif // BATTERY_H

#include "battery.h"

Battery::Battery(int percent = 100) {
    batteryPercentage = percent;
}

int Battery::decreaseBattery(int step) {
    if (batteryPercentage == 0)
        return 0;
    batteryPercentage -= step;
    return batteryPercentage;
}

bool Battery::chargeBattery() {
    batteryPercentage = 100;
    return true;
}

int Battery::getBatteryPercentage() {
    return batteryPercentage;
}

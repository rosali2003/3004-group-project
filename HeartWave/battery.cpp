#include "battery.h"

Battery::Battery() {
    batteryPercentage = 100;
}

int Battery::decreaseBattery(int step) {
    batteryPercentage -= step;
    return batteryPercentage;
}

bool Battery::chargeBattery() {
    batteryPercentage = 100;
    return true;
}

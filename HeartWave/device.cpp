#include "device.h"
#include <iostream>

using namespace std;

Device::Device()
{
    for(int i =0; i<NUMHR;i++) {
        HRvalues.push_back(HR[i]);
    }

}

QVector<int>& Device::getHRvalues(){
    return HRvalues;
}

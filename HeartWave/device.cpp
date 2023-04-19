#include "device.h"
#include <iostream>

using namespace std;

const int HR[] =  {72,88,96,64,81,77,92,78,83,71,68,79,91,85,77,80,73,\
    67,84,89,70,76,94,75,82,98,66,79,87,71,95,63,90,81,76,88,72,83,99,77,69,\
    82,93,80,75,86,68,91,78,65,84,74,89,97,79,72,83,67,92,77,86,71,96,63,82,\
    76,69,87,80,91,74,83,96,70,77,88,65,79,95,73,84,98,68,81,89,72,93,67,85,76,\
    70,88,78,92,69,80,94,71,83,97,53,102,64,92,55,120,60,98,70,128,63,113,57,106,\
    67,122,61,98,72,126,58,104,66,118,59,100, 71,132,56,112,68,124,65,99,74,130,\
    62,108,69,116,54,102,75,134,57,110,73,120,60,104};



Device::Device()
{
    for(int i =0; i<NUMHR;i++) {
        HRvalues.push_back(HR[i]);
//        cout << "Hr values at i " << " i " << i << " hrvalue " <<HRvalues.at(i) << endl;
    }

}

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
}

#include "display.h"

// constructors
Display::Display()
{
    // initialize variables
    numScreens = 2;
    currScreen = 0;

    // setup list with screen names
    QStringList list;
    list << "Begin Session" << "Session History";

    // setup the model to be added to the listView widget
    model = new QStringListModel();

    // add the list to the list model
    model->setStringList(list);

}

// getters
QModelIndex Display::getCurrScreen() {return model->index(currScreen);}
QStringListModel* Display::getModel() {return model;}

// others
QModelIndex Display::goUp() {
    if(currScreen == 0) {
        currScreen = numScreens - 1;
    } else {
        currScreen--;
    }
    return model->index(currScreen);
}

QModelIndex Display::goDown() {
    if (currScreen == numScreens -1) {
        currScreen = 0;
    } else {
        currScreen++;
    }
    return model->index(currScreen);
}

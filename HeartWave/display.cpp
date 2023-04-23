#include "display.h"

// constructors
Display::Display()
{
    // initialize variables
    currScreen = 0;
    database = new HeartDB();

    // setup lists
    screens << "Begin Session" << "Session History";
    history = database->getHistoryList();

    currList = screens;
    numScreens = currList.count();

    // setup the model to be added to the listView widget
    model = new QStringListModel();

    // add the list to the list model
    model->setStringList(currList);

}

// setters
QStringListModel* Display::setModel() {
    if(currScreen == 0) {
        return nullptr;
    } else if (currScreen == 1) {
        currList = history;
    }

    numScreens = currList.count();
    currScreen = 0;
    model->setStringList(currList);
    return model;
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

QStringListModel* Display::goToMenu() {
    currList = screens;
    numScreens = currList.count();
    currScreen = 0;
    model->setStringList(currList);
    return model;
}

QStringListModel* Display::goToSummary() {
    currList = history;
    numScreens = currList.count();
    currScreen = currList.count()-1;
    model->setStringList(currList);
    return model;
}

bool Display::isMainMenu() {
    return currList == screens;
}

void Display::updateHistory(){
    history = database->getHistoryList();
}

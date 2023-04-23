#ifndef DISPLAY_H
#define DISPLAY_H
#include <QStringListModel>
#include "HeartDB.h"
#include <string.h>

class Display
{
public:
    // constructors
    Display();

    // setters
    QStringListModel* setModel();

    // getters
    QModelIndex getCurrScreen();
    QStringListModel* getModel();

    // others
    QModelIndex goUp();
    QModelIndex goDown();
    QStringListModel* goToMenu();
    QStringListModel* goToSummary();
    bool isMainMenu();
    void updateHistory();

private:
    HeartDB *database;
    QStringList screens;
    QStringList history;
    QStringList currList;
    int currScreen;
    QStringListModel* model;
    int numScreens;
};

#endif // DISPLAY_H

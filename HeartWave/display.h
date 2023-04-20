#ifndef DISPLAY_H
#define DISPLAY_H
#include <QStringListModel>
#include "view.h"
#include <string.h>

class Display
{
public:
    // constructors
    Display();

    // getters
    QModelIndex getCurrScreen();
    QStringListModel* getModel();

    // others
    QModelIndex goUp();
    QModelIndex goDown();

private:
    int currScreen;
    QStringListModel* model;
    int numScreens;
};

#endif // DISPLAY_H

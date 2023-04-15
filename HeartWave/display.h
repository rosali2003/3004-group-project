#ifndef DISPLAY_H
#define DISPLAY_H
#include <QStringListModel>
#include "view.h"


class Display
{
public:
    Display();
    View* goUp();
    View* goDown();
    View* goToMain();
    void addHistoryToNavigation(View* lastView);
    View* goBack();
private:
    View* currScreen;
    QStringListModel* screensArr;
};

#endif // DISPLAY_H

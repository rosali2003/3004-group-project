#ifndef MENU_H
#define MENU_H
#include <QList>
#include <string>
#include "view.h"


class Menu
{
public:
    Menu();
    bool addChild();
private:
    QList<Menu*> children;
    QString menuName;
    View* parentMenu;
};

#endif // MENU_H

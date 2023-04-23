#ifndef DISPLAY_H
#define DISPLAY_H
#include <QStringListModel>
#include "HeartDB.h"
#include <string.h>

/* Class Purpose: Handle the List Menus and navigation of said menus
 *
 * Data Members:
 * - HeartDB *database: Pointer to the database to retrieve and update content for the history menu
 * - QStringList screens: A list containing the contents of the main program list when the device is booted up
 * - QStringList history: A list containing all of the past sessions with their respective data
 * - QStringList currList: A variable to keep track of the current list being displayed
 * - int currScreen: A variable to keep track of the currentIndex of the list so the highlight can be displayed properly
 * - QStringListModel*: A model that mounts the current list
 * - int numScreens: keeps the number of options in the list to allow for accurate navigation
 *
 * Class Functions:
 * - QStringListModel* setModel(): when called, mounts the list corresponding to the currScreen value
 * - QModelIndex getCurrScreen(): returns the current index to highlight the list properly on the UI
 * - QStringListModel* getModel(): returns the model with the list mounted to be added to the listView
 * - QModelIndex goUp(): handles navigation when the up arrow is pressed and returns the index the UI should highlight
 * - QModelIndex goDown(): handles navigation when the down arrow is pressed and returns the index the UI should highlight
 * - QStringListModel* goToMenu(): returns the model with the screens list mounted
 * - QStringListModel* goToSummary(): returns the model with the history list mounted and currScreen set to the last index
 * - bool isMainMenu(): returns whether the current list mounted is screens
 * - void updateHistory(): updates the history list with content from the database
 */

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

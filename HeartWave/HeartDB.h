#ifndef HEARTDB_H
#define HEARTDB_H

#include <QString>
#include <QSqlDatabase>
#include <QDateTime>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include <QApplication>
#include <QStringListModel>

#include "SessionRecord.h"

/* Class Purpose: Manages interactions between application and database
 *
 * Data Members:
 * -QString STRING_DATE_FORMAT: string format of dates going in/out the database
 * -QString DB_PATH: string path of the database
 *
 * Class Functions:
 *
 * bool addSessionRecord(SessionRecord& session): adds a session record to the database, returns true if successful, false otherwise
 * bool updateProfile(int battery_level): updates battery_level in database, returns true if it was added properly, false otherwise
 * bool deleteSessions(): deletes all sessions stored in the database, returns true if successful, false otherwise
 * bool deleteSession(int index): deletes session in database whose index matches parameter index, returns true if successful, false otherwise
 * QStringList getHistoryList(): return a list of strings for each session record in the database formatted to show the session information, returns true if successful, false otherwise
 * int getBatteryLevel(): retrieves battery_level stored in database
 * QVector<SessionRecord*> getSessions(): returns a vector of SessionRecord* with all sessions stored in the database
 *
 * bool initialize_db(): Initalizes the database to ensure profiles and sessions tables created, returns true if successful, fasle otherwise
 */

class HeartDB {

public:
    HeartDB();
    static const QString DB_PATH;
    const QString STRING_DATE_FORMAT = "yyyy-MM-dd hh:mm";
    bool addSessionRecord(SessionRecord& session);
    bool updateProfile(int battery_level);
    bool deleteSessions();
    bool deleteSession(int index);
    int getBatteryLevel();
    QStringList getHistoryList();
    QVector<SessionRecord*> getSessions();

private:
    bool initialize_db();
};

#endif // HEARTDB_H

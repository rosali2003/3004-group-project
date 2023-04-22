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
 * -QSqlDatabase heartDB: the database object
 * -QString STRING_DATE_FORMAT: formats of dates going in/out the database
 * -QString DB_PATH: path of the database
 *
 * Class Functions:
 * Getters for sessions and battery_level
 *
 * bool addSessionRecord(QDateTime date, int duration, float avg_coherence): adds a session record to the database, returns true if it was added properly, false otherwise
 * bool addProfile(int id, double batterLvl): adds a profile to the database, returns true if it was added properly, false otherwise
 *
 * bool initialize_db(): Initalizes the database
 */

class HeartDB {

public:
    static const QString DB_PATH;
    const QString STRING_DATE_FORMAT = "yyyy-MM-dd hh:mm";

    HeartDB();
    bool addSessionRecord(SessionRecord& session);
    bool updateProfile(int battery_level);
    bool deleteSessions();
    bool deleteSession(int index);
    QStringList getHistoryList();

    int getBatteryLevel();
    QVector<SessionRecord*> getSessions();


private:
    bool addRecord(const QString& tableName, const QString& name, const QDateTime& time, int powerLevel, int duration);
    bool initialize_db();
};

#endif // HEARTDB_H

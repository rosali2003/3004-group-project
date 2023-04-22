#include "HeartDB.h"

const QString HeartDB::DB_PATH = "/database/heart.db";


/*
 * Create a new DBManager to a existing denas database, defined by DBManager::DATABASE_PATH
 *
 * Throws:
 *  If the database could not be opened
 */
HeartDB::HeartDB() {

    QSqlDatabase heartDB = QSqlDatabase::addDatabase("QSQLITE");
    heartDB.setDatabaseName("heart.db");

    if (!heartDB.open()) {
        throw "Error: Database could not be opened";
    }

    if (!initialize_db()) {
        throw "Error: Database could not be initialized";
    }
}

bool HeartDB::initialize_db() {
    QSqlDatabase heartDB = QSqlDatabase::database();

    heartDB.transaction();

    QSqlQuery query;
    qDebug() << "Creating table profiles: " << query.exec("CREATE TABLE IF NOT EXISTS profiles ( pid INTEGER NOT NULL UNIQUE PRIMARY KEY,battery_level INTEGER NOT NULL);");
    qDebug() << "Creating table sessions: " << query.exec("CREATE TABLE IF NOT EXISTS sessions ( sid INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT,date TEXT NOT NULL,duration REAL NOT NULL,avg_coherence REAL NOT NULL,achievement_score REAL NOT NULL);");

    return heartDB.commit();
}

int HeartDB::getBatteryLevel(){
    QSqlDatabase db = QSqlDatabase::database();

    db.transaction();

    QSqlQuery query;
    query.prepare("SELECT * FROM profiles WHERE pid=1;");
    qDebug() << "get battery level query: " << query.exec();

    db.commit();

    if(!query.next()){
        qDebug() << "profile not found";
        query.exec("INSERT INTO profiles (pid, battery_level) VALUES (1, 100);");
        return 100;
    }

    qDebug() << "profile id: " << query.value(0).toString();
    return query.value(1).toInt();

}

bool HeartDB::updateProfile(int battery_level){
    QSqlDatabase db = QSqlDatabase::database();

    db.transaction();

    QSqlQuery query;
    query.exec("DROP TABLE profiles;");
    query.exec("CREATE TABLE IF NOT EXISTS profiles ( pid INTEGER NOT NULL UNIQUE PRIMARY KEY,battery_level INTEGER NOT NULL);");

    query.prepare("INSERT INTO profiles (pid, battery_level) VALUES (:pid, :battery_level);");
    query.bindValue(":pid", 1);
    query.bindValue(":battery_level", battery_level);
    if(query.exec()) {
        qDebug() << "update profile query successfull";
    }
    else {
        qDebug() << "Failed to update row: " << query.lastError().text();
    }


    return db.commit();
}

bool HeartDB::addSessionRecord(SessionRecord& session){
    QSqlDatabase db = QSqlDatabase::database();

    db.transaction();

    QSqlQuery query;
    query.prepare("INSERT INTO sessions (date, duration, avg_coherence, achievement_score) VALUES (:date, :duration, :avg_coherence, :achievement_score);");
    query.bindValue(":date", session.getDate().toString(STRING_DATE_FORMAT));
    query.bindValue(":duration", session.getDuration());
    query.bindValue(":avg_coherence", session.getAvgCoherence());
    query.bindValue(":achievement_score", session.getAchievementScore());
    qDebug() << "add session query: " << query.exec();

    return db.commit();
}

QVector<SessionRecord*> HeartDB::getSessions(){
    QSqlDatabase db = QSqlDatabase::database();

    db.transaction();

    QSqlQuery query;
    query.prepare("SELECT * FROM sessions;");
    qDebug() << "get sessions query: " << query.exec();

    if(!db.commit()){
        throw "Error: could not query sessions";
    }

    QVector<SessionRecord*> sessions;
    while(query.next()){
        QDateTime date = QDateTime::fromString(query.value(1).toString(), STRING_DATE_FORMAT);
        sessions.append(new SessionRecord(date, query.value(2).toFloat(), query.value(3).toFloat(), query.value(4).toFloat()));
    }

    return sessions;
}

bool HeartDB::deleteSessions(){
    QSqlDatabase db = QSqlDatabase::database();

    db.transaction();

    QSqlQuery query;
    query.prepare("DROP TABLE sessions;");
    qDebug() << "drop sessions query: " << query.exec();
    query.prepare("CREATE TABLE IF NOT EXISTS sessions ( sid INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT,date TEXT NOT NULL,duration REAL NOT NULL,avg_coherence REAL NOT NULL,achievement_score REAL NOT NULL);");
    qDebug() << "re-create table sessions query: " << query.exec();

    return db.commit();
}

bool HeartDB::deleteSession(int index) {
    QVector<SessionRecord*> sessionsVector = getSessions();
    SessionRecord* session = sessionsVector.value(index);

    QSqlDatabase db = QSqlDatabase::database();

    db.transaction();

    QSqlQuery query;
    query.prepare("DELETE FROM sessions WHERE date=:date AND duration=:duration AND avg_coherence=:avg_coherence;");
    query.bindValue(":date", session->getDate().toString(STRING_DATE_FORMAT));
    query.bindValue(":duration", session->getDuration());
    query.bindValue(":avg_coherence", session->getAvgCoherence());
    qDebug() << query.exec();

    return db.commit();
}

QStringList HeartDB::getHistoryList() {
    QVector<SessionRecord*> sessionsVector = getSessions();
    QStringList list;

    foreach(SessionRecord* record, sessionsVector) {
        QString str = record->getDate().toString() + "\nDuration: " + QString::number(record->getDuration(), 'f', 1) + "s\nAvg Coherence: " + QString::number(record->getAvgCoherence(), 'f', 2) + "\nAchievement Score: " + QString::number(record->getAchievementScore(), 'f', 2);
        list << str;
    }

    return list;
}

#ifndef RUNNERDATABASE_H
#define RUNNERDATABASE_H

#include <QString>
#include <QtSql>
#include <QList>
#include <QString>
#include <QDebug>
#include "Athlete.h"
#include "RunningProfile.h"
#include "RunningEvent.h"
#include "RunningTime.h"

class RunnerDatabase
{
public:
    RunnerDatabase();
    ~RunnerDatabase();
    void test();
    //Methods related to the Athlete Table
    int addAthlete(Athlete&);
    bool removeAthlete(int);
    QList<Athlete> findAthletes(QString);

    //Methods related to the Profile Table
    int addProfile(RunningProfile&);
    QList<RunningProfile> returnAllProfiles();
    bool updateProfile(RunningProfile);
    bool removeProfile(RunningProfile);

    //Methods related to the Event Table
    int addEvent(RunningEvent&);
    bool updateEvent(RunningEvent);
    QList<RunningEvent> findEventsForDate(int,QDate);
    bool removeEvent(int);

    //Utility functions
    static QString convertAthleteListToString(QList<Athlete>);

    //These are the default strings used for tables
    static const QString RUNNER_TABLE_NAME;
    static const QString EVENT_TABLE_NAME;
    static const QString PROFILE_TABLE_NAME;
    //These are common columns in all tables
    static const QString ID_COLUMN;
    static const QString NAME_COLUMN;
    //These are specialized columns within certain tables
    static const QString RUNNER_COLUMN;
    static const QString EVENT_TIME_COLUMN;
    static const QString EVENT_DATE_COLUMN;
    static const QString ATHLETE_LIST_COLUMN;
private:
    QSqlDatabase DefaultDatabase;
};

#endif // RUNNERDATABASE_H

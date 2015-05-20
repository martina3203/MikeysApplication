#ifndef RUNNERDATABASE_H
#define RUNNERDATABASE_H

#include <QString>
#include <QtSql>
#include <QDebug>
#include "Athlete.h"
#include "RunningEvent.h"
#include "RunningTime.h"

class RunnerDatabase
{
public:
    RunnerDatabase();
    ~RunnerDatabase();
    addAthlete(Athlete);
    addEvent(RunningEvent);
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
    static const QString RUNNER_LIST_COLUMN;
private:
    QSqlDatabase DefaultDatabase;
};

#endif // RUNNERDATABASE_H

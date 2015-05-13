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
private:
    QSqlDatabase DefaultDatabase;

    //These are the strings used for default table names and column names
    const QString RUNNER_TABLE_NAME = "RUNNERS";
    const QString EVENT_TABLE_NAME = "EVENTS";
};

#endif // RUNNERDATABASE_H

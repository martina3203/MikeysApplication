#ifndef RUNNERDATABASE_H
#define RUNNERDATABASE_H

#include <QString>
#include <QtSql>

class RunnerDatabase
{
public:
    RunnerDatabase();
private:
    QSqlDatabase DefaultDatabase;
};

#endif // RUNNERDATABASE_H

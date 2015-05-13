#include "RunnerDatabase.h"

RunnerDatabase::RunnerDatabase()
{
    DefaultDatabase = QSqlDatabase::addDatabase("QSQLITE");
    DefaultDatabase.setDatabaseName("LocalDatabase");
    if (!DefaultDatabase.open())
    {

    }
    else
    {

    }
}


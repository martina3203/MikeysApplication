#include "RunnerDatabase.h"

RunnerDatabase::RunnerDatabase()
{
    //Create Database connection using a default connection
    DefaultDatabase = QSqlDatabase::addDatabase("QSQLITE");
    //Create or open a file called LocalDatabase.db
    DefaultDatabase.setDatabaseName("LocalDatabase.db");
    if (!DefaultDatabase.open())
    {
        qDebug() << "Error: Opening Database.";
    }
    else
    {
        qDebug() << "Database Opened.";
    }

    //Create tables as necessary
    QSqlQuery databaseQuery;
    if (!databaseQuery.exec("CREATE TABLE stupid (poop int);"))
    {
        qDebug() << "Failed to Create Table";
    }

}

RunnerDatabase::~RunnerDatabase()
{
    //Close connection
    DefaultDatabase.close();
    QSqlDatabase::removeDatabase("LocalDatabase.db");
}

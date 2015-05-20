#include "RunnerDatabase.h"

//These are the constant strings names used for Table access within the database.
const QString RunnerDatabase::RUNNER_TABLE_NAME = "RUNNERS";
const QString RunnerDatabase::EVENT_TABLE_NAME = "EVENTS";
const QString RunnerDatabase::PROFILE_TABLE_NAME = "PROFILE";
//These are common columns in all tables
const QString RunnerDatabase::ID_COLUMN = "ID";
const QString RunnerDatabase::NAME_COLUMN = "NAME";
//These are specialized columns within certain tables
const QString RunnerDatabase::RUNNER_COLUMN = "RUNNER_ID";
const QString RunnerDatabase::EVENT_TIME_COLUMN = "EVENT_TIME";
const QString RunnerDatabase::EVENT_DATE_COLUMN = "EVENT_DATE";
const QString RunnerDatabase::RUNNER_LIST_COLUMN = "RUNNER_LIST";


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
    QString tableCreation;
    //Runner Table
    if (!DefaultDatabase.tables().contains(RUNNER_TABLE_NAME))
    {
        tableCreation = "CREATE TABLE " + RUNNER_TABLE_NAME + " (" + ID_COLUMN + " integer, " +
                   NAME_COLUMN + " varchar(80));";
        if (!databaseQuery.exec(tableCreation))
        {
            qDebug() << "Failed to Create Runner Table.";
        }
        else
        {
            qDebug() << "Runner Table Created.";
        }
    }
    //Runner Event Table
    if (!DefaultDatabase.tables().contains(EVENT_TABLE_NAME))
    {
        tableCreation = "CREATE TABLE " + EVENT_TABLE_NAME + " (" + ID_COLUMN + " integer, " + NAME_COLUMN + " varchar(80), "
                + RUNNER_COLUMN + " integer, " + EVENT_DATE_COLUMN + " varchar(25));";
        if (!databaseQuery.exec(tableCreation))
        {
            qDebug() << "Failed to Create Event Table.";
        }
        else
        {
            qDebug() << "Event Table Created.";
        }
    }
    //Profile Table
    if (!DefaultDatabase.tables().contains(PROFILE_TABLE_NAME))
    {
        tableCreation = "CREATE TABLE " + PROFILE_TABLE_NAME + " (" + ID_COLUMN + " integer, " + RUNNER_LIST_COLUMN + " TEXT);";
        if (!databaseQuery.exec(tableCreation))
        {
            qDebug() << "Failed to Create Profile Table.";
        }
        else
        {
            qDebug() << "Profile Table Created.";
        }
    }

}

RunnerDatabase::~RunnerDatabase()
{
    //Close connection
    DefaultDatabase.close();
    QSqlDatabase::removeDatabase("LocalDatabase.db");
}

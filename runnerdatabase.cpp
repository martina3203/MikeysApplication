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
const QString RunnerDatabase::ATHLETE_LIST_COLUMN = "RUNNER_LIST";


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
        tableCreation = "CREATE TABLE " + RUNNER_TABLE_NAME + " (" + ID_COLUMN + " integer PRIMARY KEY AUTOINCREMENT, " +
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
        tableCreation = "CREATE TABLE " + EVENT_TABLE_NAME + " (" + ID_COLUMN + " integer PRIMARY KEY AUTOINCREMENT, " + NAME_COLUMN + " varchar(80), "
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
        tableCreation = "CREATE TABLE " + PROFILE_TABLE_NAME + " (" + ID_COLUMN + " integer PRIMARY KEY AUTOINCREMENT, "
                + NAME_COLUMN + " varchar(80), " + ATHLETE_LIST_COLUMN + " TEXT);";
        if (!databaseQuery.exec(tableCreation))
        {
            qDebug() << "Failed to Create Profile Table.";
        }
        else
        {
            qDebug() << "Profile Table Created.";
        }
    }

    test();

}

RunnerDatabase::~RunnerDatabase()
{
    //Close connection
    DefaultDatabase.close();
    QSqlDatabase::removeDatabase("LocalDatabase.db");
}

void RunnerDatabase::test()
{
    Athlete testAthlete;
    int result;
    //Adding of Athletes
    qDebug() << "Start Athlete Testing:";
    testAthlete.setAthleteName("Aaron Martin");
    result = addAthlete(testAthlete);
    qDebug() << result;

    //Adding of Profiles
    qDebug() << "Start Profile Testing:";
    RunningProfile testProfile;
    testProfile.setName("Test Profile");
    addProfile(testProfile);
    //Query of All Profiles
    QList<RunningProfile> testList = returnAllProfiles();
    for (int i = 0; i < testList.size(); i++)
    {
        testProfile = testList.at(i);
        qDebug() << testProfile.returnName();
    }

    //Adding of events
    qDebug() << "Start Event Testing:";
    RunningEvent testEvent;
    RunningTime newTime = convertStringToTime("4:46.3");
    testEvent.setTime(newTime);
    result = addEvent(testEvent);
    qDebug() << result;
}

//Adds an athlete to the database
int RunnerDatabase::addAthlete(Athlete &newAthlete)
{
    QSqlQuery databaseQuery;
    int IDNumber = 0;
    QString athleteName = newAthlete.returnName();
    QString command = "INSERT INTO " + RUNNER_TABLE_NAME + " (" + NAME_COLUMN + ") VALUES ('" + athleteName + "');";
    if (!databaseQuery.exec(command))
    {
        qDebug() << "Failed to add Athlete " << newAthlete.returnName() << ".";
    }
    else
    {
        //Update the value of the ID in the newAthlete
        IDNumber = databaseQuery.lastInsertId().toInt();
        newAthlete.setID(IDNumber);
    }
    return IDNumber;
}

//Removes an athlete from the database based on it's ID value
bool RunnerDatabase::removeAthlete(int IDNumber)
{
    QSqlQuery databaseQuery;
    QString command = "DELETE FROM " + RUNNER_TABLE_NAME + " WHERE " + ID_COLUMN + " = " + QString::number(IDNumber) + ";";
    if (!databaseQuery.exec(command))
    {
        qDebug() << "Failed to remove Athlete from Database.";
        return false;
    }
    return true;
}

//Parse a comma separated string to find corresponding Athletes by ID
QList<Athlete> RunnerDatabase::findAthletes(QString IDList)
{
    QSqlQuery databaseQuery;
    QString command = "";
    QList<Athlete> athleteList;
    QString buildString = "";
    for (int i = 0; i < IDList.size(); i++)
    {
        //Parse string
        QString buildString;
        if (IDList.at(i) != ',')
        {
            buildString = buildString + IDList.at(i);
        }
        else if (buildString != "")
        {
            //Try to find this value in the database
            command = "SELECT * FROM " + RUNNER_TABLE_NAME + " WHERE "
                    + ID_COLUMN + " = " + buildString + ";";
            if (databaseQuery.exec(command))
            {
                //If found, add to list
                databaseQuery.next();
                QString athleteName = databaseQuery.value(1).toString();
                int athleteID = databaseQuery.value(0).toInt();
                Athlete newAthlete;
                newAthlete.setAthleteName(athleteName);
                newAthlete.setID(athleteID);
                //Add to list
                athleteList.append(newAthlete);
            }
            //Reset string
            buildString = "";
        }
    }
    return athleteList;
}

//Adds a profile to the database
int RunnerDatabase::addProfile(RunningProfile &newProfile)
{
    QSqlQuery databaseQuery;
    QString command;
    //First we must acquire all of the ID's of athletes that correspond to the newProfile
    //This is stored as a string in the database of comma seperated numbers
    QList<Athlete> athleteList = newProfile.returnAllAthletes();
    QString profileName = newProfile.returnName();
    QString IDList = convertAthleteListToString(newProfile.returnAllAthletes());
    int IDNumber = 0;
    command = "INSERT INTO " + PROFILE_TABLE_NAME + " (" + NAME_COLUMN + ", " + ATHLETE_LIST_COLUMN + ") VALUES ('"
            + profileName + "', '" + IDList + "');";
    if (!databaseQuery.exec(command))
    {
        qDebug() << "Failed to add Profile to Database.";
    }
    else
    {
        IDNumber = databaseQuery.lastInsertId().toInt();
        newProfile.setID(IDNumber);
    }
    return IDNumber;
}

//Returns all profiles from the database
QList<RunningProfile> RunnerDatabase::returnAllProfiles()
{
    QList<RunningProfile> profileList;
    QSqlQuery databaseQuery;
    QString command;
    //Grab all of the profiles from the database.
    command = "SELECT * FROM " + PROFILE_TABLE_NAME + ";";
    if (!databaseQuery.exec(command))
    {
        qDebug() << "Failed to return all Profiles from Database.";
    }
    else
    {
        while(databaseQuery.next())
        {
            //Add each profile to the list
            RunningProfile returnedProfile;
            //Grab ID
            int IDNumber = databaseQuery.value(0).toInt();
            returnedProfile.setID(IDNumber);
            //Grab Name
            QString profileName = databaseQuery.value(1).toString();
            returnedProfile.setName(profileName);
            //Now we must collect all of the athletes that correspond to the Profile
            QString athleteList = databaseQuery.value(2).toString();
            QList<Athlete> convertedList = findAthletes(athleteList);
            returnedProfile.updateAthleteList(convertedList);
            profileList.append(returnedProfile);
        }
    }
    return profileList;
}

//Updates a specific profile in the database
bool RunnerDatabase::updateProfile(RunningProfile theProfile)
{
    QSqlQuery databaseQuery;
    QString command;
    //Acquire attributes
    QString profileName = theProfile.returnName();
    int IDNumber = theProfile.returnID();
    QString athleteList = convertAthleteListToString(theProfile.returnAllAthletes());
    //Build SQL Command
    command = "UPDATE " + PROFILE_TABLE_NAME + " SET " + NAME_COLUMN + " = '" + profileName + "', " +
            ATHLETE_LIST_COLUMN + " = '" +  athleteList + "' WHERE " + ID_COLUMN + " = " + IDNumber + ";";
    if (!databaseQuery.exec(command))
    {
        qDebug() << "Failed to update Profile '" + profileName + "' in Database.";
        return false;
    }
    return true;
}

int RunnerDatabase::addEvent(RunningEvent &newEvent)
{
    QSqlQuery databaseQuery;
    QString command;
    int IDNumber = 0;
    QString eventName = newEvent.returnEventName();
    QString eventTime = newEvent.returnTime().toString();
    qDebug() << eventTime;

    return IDNumber;
}

bool RunnerDatabase::updateEvent(RunningEvent theEvent)
{
    QSqlQuery databaseQuery;
    QString command;
    return true;
}

QList<RunningEvent> RunnerDatabase::findEventsForDate(int athleteID, QString theDate)
{
    QList<RunningEvent> eventList;
    QSqlQuery databaseQuery;
    QString command;
    return eventList;
}

bool RunnerDatabase::removeEvent(int IDNumber)
{
    QSqlQuery databaseQuery;
    QString command;
    return true;
}

// UTILITY FUNCTIONS FROM THIS POINT ON

QString RunnerDatabase::convertAthleteListToString(QList<Athlete> theList)
{
    QString IDList = "";
    for (int i = 0; i < theList.size(); i++)
    {
        //Grab every ID
        QString convertedNumber = "";
        Athlete currentAthlete = theList.at(i);
        int currentAthleteID = currentAthlete.returnID();
        convertedNumber = QString::number(currentAthleteID);
        IDList = IDList + convertedNumber + ",";
    }
    return IDList;
}

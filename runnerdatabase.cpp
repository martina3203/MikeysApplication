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
const QString RunnerDatabase::EVENT_ORDER_COLUMN = "EVENT_ORDER";
const QString RunnerDatabase::ATHLETE_LIST_COLUMN = "RUNNER_LIST";


//These are just normal constants
const QString RunnerDatabase::DATE_FORMAT = "MM.dd.yyyy";

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
    //Event Table
    if (!DefaultDatabase.tables().contains(EVENT_TABLE_NAME))
    {
        tableCreation = "CREATE TABLE " + EVENT_TABLE_NAME + " (" + ID_COLUMN + " integer PRIMARY KEY AUTOINCREMENT, " + NAME_COLUMN + " varchar(80), "
                + RUNNER_COLUMN + " integer, " + EVENT_TIME_COLUMN + " varchar(30), " + EVENT_DATE_COLUMN + " varchar(25), " + EVENT_ORDER_COLUMN + " integer);";
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
}

RunnerDatabase::~RunnerDatabase()
{
    //Close connection
    DefaultDatabase.close();
    QSqlDatabase::removeDatabase("LocalDatabase.db");
}

void RunnerDatabase::test()
{
    /*
     * ATHLETES DATABASE SECTION
     */
    Athlete testAthlete;
    int result;
    //Adding of Athletes
    qDebug() << "Start Athlete Testing:";
    testAthlete.setAthleteName("Aaron Martin");
    result = addAthlete(testAthlete);
    if (result != 0)
    {
        qDebug() << "Athlete successfully added.";
    }
    else
    {
        qDebug() << "Athlete failed to be added.";
        return;
    }

    //Finding Athletes based on a comma separated list
    QString IDList = QString::number(result) + ",";
    Athlete newAthlete;
    newAthlete.setAthleteName("Mike Cox");
    result = addAthlete(newAthlete);
    IDList = IDList + QString::number(result) + ",";
    QList<Athlete> testAthleteList = findAthletes(IDList);
    for (int i = 0; i < testAthleteList.size(); i++)
    {
        Athlete currentAthlete = testAthleteList.at(i);
        QString name = currentAthlete.returnName();
        int ID = currentAthlete.returnID();
        QString IDConverted = QString::number(ID);
        qDebug() << "Athlete Name: "  + name + " || Athlete ID: " + IDConverted;
    }
    if (testAthleteList.size() == 0)
    {
        qDebug() << "No Athletes in List. Error in Database.";
        return;
    }

    //Removing the new athletes
    result = removeAthlete(testAthlete.returnID());
    if (result != 1)
    {
        qDebug() << "Failed to remove Athletes from Database.";
        return;
    }
    result = removeAthlete(newAthlete.returnID());
    if (result != 1)
    {
        qDebug() << "Failed to remove Athletes from Database.";
        return;
    }
    qDebug() << "Test Athletes removed.";


    //Adding of Profiles
    qDebug() << "Start Profile Testing:";
    RunningProfile testProfile;
    testProfile.setName("Test Profile");
    addProfile(testProfile);
    testProfile.setName("Not a test profile");
    addProfile(testProfile);
    //Query of All Profiles
    QList<RunningProfile> testList = returnAllProfiles();
    qDebug() << "Find all Profiles";
    for (int i = 0; i < testList.size(); i++)
    {
        testProfile = testList.at(i);
        qDebug() << testProfile.returnName();
    }
    qDebug() << "If there is no values, we have a problem.";
    //Update Profile
    qDebug() << "Testing Updating by changing profile name";
    testProfile.setName("Not Test Profile");
    updateProfile(testProfile);
    testList = returnAllProfiles();
    for (int i = 0; i < testList.size(); i++)
    {
        testProfile = testList.at(i);
        qDebug() << testProfile.returnName();
    }

    //Finally, remove profile
    qDebug() << "Removing test profile.";
    if (!removeProfile(testProfile.returnID()))
    {
        qDebug() << "Unable to remove test profile.";
        return;
    }
    else
    {
        qDebug() << "Test Profile successfully removed.";
    }

    //Adding of events
    qDebug() << "Start Event Testing:";
    RunningEvent testEvent;
    QDate testDate;
    testDate.setDate(1993,5,3);
    QString theDate = testDate.toString(DATE_FORMAT);
    qDebug() << theDate;
    RunningTime newTime = convertStringToTime("4:46.3");
    testEvent.setTime(newTime);
    testEvent.setName("400 Meter Dash");
    testEvent.setAthleteID(6);
    testEvent.setDate(testDate);

    qDebug() << "Adding Test Event.";
    result = addEvent(testEvent);
    if (result != 0)
    {
        qDebug() << "Successfully added Event.";
    }
    else
    {
        qDebug() << "Failed to add Event.";
        return;
    }

    qDebug() << "Update Event.";
    newTime = convertStringToTime("2:50:00.60");
    testEvent.setTime(newTime);
    result = updateEvent(testEvent);
    if (result == 1)
    {
        qDebug() << "Event successfully updated.";
    }
    else
    {
        qDebug() << "Failed to update Event.";
        return;
    }

    qDebug() << "Searching for event based on date";
    QList<RunningEvent> eventList = findEventsForDate(testEvent.returnAthleteID(),testDate);
    for (int i = 0; i < eventList.size(); i++)
    {
        testEvent = eventList.at(i);
        qDebug() << testEvent.returnEventName();
        qDebug() << testEvent.returnDate().toString(DATE_FORMAT);
        qDebug() << testEvent.returnTime().toString();
    }
    if (eventList.size() == 0)
    {
        qDebug() << "Event list is empty. Error in Database.";
    }

    qDebug() << "Deleting an event from the database";
    if (removeEvent(testEvent.returnID()))
    {
        qDebug() << "Event successfully deleted.";
    }
    else
    {
        qDebug() << "Failed to delete event.";
    }
}

//Adds an athlete to the database
int RunnerDatabase::addAthlete(Athlete &newAthlete)
{
    QSqlQuery databaseQuery;
    int IDNumber = 0;
    QString athleteName = newAthlete.returnName();
    //Ensure SQL compatibility
    SQLString(athleteName);
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
            else
            {
                qDebug() << "Unable to find value in Database: " + buildString;
            }
            //Reset string
            buildString = "";
        }
    }
    QuickSort(athleteList,0,athleteList.size()-1);
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
    SQLString(profileName);
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
    //Ensure SQL compatibility
    SQLString(profileName);
    int IDNumber = theProfile.returnID();
    QString IDNumberString = QString::number(IDNumber);
    QString athleteList = convertAthleteListToString(theProfile.returnAllAthletes());
    //Build SQL Command
    command = "UPDATE " + PROFILE_TABLE_NAME + " SET " + NAME_COLUMN + " = '" + profileName + "', " +
            ATHLETE_LIST_COLUMN + " = '" +  athleteList + "' WHERE " + ID_COLUMN + " = " + IDNumberString + ";";
    if (!databaseQuery.exec(command))
    {
        qDebug() << "Failed to update Profile '" + profileName + "' in Database.";
        return false;
    }
    return true;
}

//Removes a profile in the database
bool RunnerDatabase::removeProfile(int IDNumber)
{
    QSqlQuery databaseQuery;
    QString command = "DELETE FROM " + PROFILE_TABLE_NAME + " WHERE " + ID_COLUMN + " = " + QString::number(IDNumber) + ";";
    if (!databaseQuery.exec(command))
    {
        qDebug() << "Failed to remove Profile from Database.";
        return false;
    }
    return true;
}

//Adds an event to the database
int RunnerDatabase::addEvent(RunningEvent &newEvent)
{
    QSqlQuery databaseQuery;
    QString command;
    int IDNumber = 0;
    QString eventName = newEvent.returnEventName();
    SQLString(eventName);
    QString eventTime = newEvent.returnTime().toString();
    SQLString(eventTime);
    QString eventDate = newEvent.returnDate().toString(DATE_FORMAT);
    SQLString(eventDate);
    int athleteID = newEvent.returnAthleteID();
    int eventOrder = newEvent.returnEventOrderNumber();
    //Must convert to be accepted within the command statement
    QString athleteIDString = QString::number(athleteID);
    QString eventOrderString = QString::number(eventOrder);
    //Now we create our insert statement
    command = "INSERT INTO " + EVENT_TABLE_NAME + " (" + NAME_COLUMN + ", " + EVENT_DATE_COLUMN + ", " +
            EVENT_TIME_COLUMN + ", " + RUNNER_COLUMN + ", " + EVENT_ORDER_COLUMN + ") VALUES ('" + eventName + "', '" + eventDate +
            "', '" + eventTime + "', " + athleteIDString + ", " + eventOrderString + ");";
    //Execute
    if (!databaseQuery.exec(command))
    {
        qDebug() << "Failure to add Event '" + eventName + "' to Database.";
    }
    else
    {
        IDNumber = databaseQuery.lastInsertId().toInt();
        newEvent.setID(IDNumber);
    }
    return IDNumber;
}

bool RunnerDatabase::updateEvent(RunningEvent theEvent)
{
    QSqlQuery databaseQuery;
    QString command;
    int eventID = theEvent.returnID();
    QString eventIDString = QString::number(eventID);
    QString eventName = theEvent.returnEventName();
    SQLString(eventName);
    QString eventTime = theEvent.returnTime().toString();
    SQLString(eventTime);
    QString eventDate = theEvent.returnDate().toString(DATE_FORMAT);
    SQLString(eventDate);
    int athleteID = theEvent.returnAthleteID();
    int eventOrder = theEvent.returnEventOrderNumber();
    QString athleteIDString = QString::number(athleteID);
    command = "UPDATE " + EVENT_TABLE_NAME + " SET " + NAME_COLUMN + " ='" + eventName + "', " +
            EVENT_TIME_COLUMN + "='" + eventTime + "', " + EVENT_DATE_COLUMN + " ='" + eventDate +
            "'," + RUNNER_COLUMN + "=" + athleteIDString + ", " + EVENT_ORDER_COLUMN + "=" + eventOrder + " WHERE " + ID_COLUMN + "=" + eventIDString;
    if (!databaseQuery.exec(command))
    {
        qDebug() << "Failed to update Event " + eventName + " in Database.";
        return false;
    }
    return true;
}

QList<RunningEvent> RunnerDatabase::findEventsForDate(int athleteID, QDate theDate)
{
    QList<RunningEvent> eventList;
    QSqlQuery databaseQuery;
    //Convert QDate to string
    QString dateString = theDate.toString(DATE_FORMAT);
    QString command = "SELECT * FROM " + EVENT_TABLE_NAME + " WHERE (" + RUNNER_COLUMN + " = " + QString::number(athleteID) + " AND "
            + EVENT_DATE_COLUMN + " = '" + dateString + "');";
    if (databaseQuery.exec(command))
    {
        while (databaseQuery.next())
        {
            //Create and retrieve each field of the event
            //Convert values as necessary
            RunningEvent newEvent;
            int ID = databaseQuery.value(0).toInt();
            QString eventName = databaseQuery.value(1).toString();
            int athleteID = databaseQuery.value(2).toInt();
            int eventOrder = databaseQuery.value(5).toInt();

            //Acquire and convert time
            QString eventTimeString = databaseQuery.value(3).toString();
            RunningTime eventTime = convertStringToTime(eventTimeString);

            //Acquire and convert date
            //Date is in the format of 'MM.DD.YYYY'
            QString eventDateString = databaseQuery.value(4).toString();
            QDate eventDate;
            //Acquire each field individually and convert to integer value
            int month = eventDateString.section(".",0,0).toInt();
            int day = eventDateString.section(".",1,1).toInt();
            int year = eventDateString.section(".",2,2).toInt();
            eventDate.setDate(year,month,day);

            //Set values
            newEvent.setID(ID);
            newEvent.setAthleteID(athleteID);
            newEvent.setName(eventName);
            newEvent.setTime(eventTime);
            newEvent.setDate(eventDate);
            newEvent.setEventOrderNumber(eventOrder);
            //Add to list
            eventList.push_back(newEvent);
        }
        //Finally sort list
        QuickSort(eventList,0,(eventList.size()-1));
    }
    else
    {
        qDebug() << "Failed to find events by date in Database.";
    }
    return eventList;
}

bool RunnerDatabase::removeEvent(int IDNumber)
{
    QSqlQuery databaseQuery;
    QString command = "DELETE FROM " + EVENT_TABLE_NAME + " WHERE " + ID_COLUMN + " = " + QString::number(IDNumber) + ";";
    if (!databaseQuery.exec(command))
    {
        qDebug() << "Failed to remove Athlete from Database.";
        return false;
    }
    return true;
}

//Finds Events for a given list of Athletes
QList<QList<RunningEvent> > RunnerDatabase::findEventsForGivenAthletes(QList<Athlete> theAthletes, QDate givenDate)
{
    QList<QList<RunningEvent> > returnedList;
    for (int i = 0; i < theAthletes.size(); i++)
    {
        Athlete currentAthlete = theAthletes.at(i);
        int IDNumber = currentAthlete.returnID();
        QList<RunningEvent> eventList = findEventsForDate(IDNumber,givenDate);
        returnedList.append(eventList);
    }
    //The list has Event entries based on athlete
    //Athlete[0] has it's entries in returnedList[0]
    return returnedList;
}



//UTILITY FUNCTIONS FROM THIS POINT ON

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

//This replaces characters that break SQL statements with valid characters that maintain the meaning
void SQLString(QString &theString)
{
    theString.replace("'","''");
}

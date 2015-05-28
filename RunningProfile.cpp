#include "RunningProfile.h"

RunningProfile::RunningProfile()
{
    //Constructor
    ProfileName = "";
    IDNumber = 0;
}

void RunningProfile::test()
{
    setName("Test Profile");

}


void RunningProfile::setName(QString newName)
{
   ProfileName = newName;
}

void RunningProfile::setID(int newID)
{
    IDNumber = newID;
}

QString RunningProfile::returnName()
{
    return ProfileName;
}

int RunningProfile::returnID()
{
    return IDNumber;
}

void RunningProfile::addAthlete(Athlete newAthlete)
{
    ListOfAthletes.push_back(newAthlete);
}

void RunningProfile::updateAthleteList(QList<Athlete> newList)
{
    ListOfAthletes = newList;
}

void RunningProfile::removeAthlete(QString AthleteName)
{
    //Find Athlete
    for (int i = 0; i < ListOfAthletes.size(); i++)
    {
        //Remove Athlete
        Athlete currentAthlete = ListOfAthletes.at(i);
        if (AthleteName == currentAthlete.returnName())
        {
            //Once removed, update list
            for (int j = i; j < ListOfAthletes.size(); j++)
            {
                ListOfAthletes.replace(j,ListOfAthletes.at(j+1));
            }
            return;
        }
    }
}

Athlete RunningProfile::returnAthleteInformation(QString AthleteName)
{
    Athlete currentAthlete;
    for (int i = 0; i < ListOfAthletes.size(); i++)
    {
        currentAthlete = ListOfAthletes.at(i);
        if (AthleteName == currentAthlete.returnName())
        {
            return currentAthlete;
        }
    }
    //This is the fail statement
    currentAthlete.setAthleteName("FAILED");
    return currentAthlete;
}

QList<Athlete> RunningProfile::returnAllAthletes()
{
    return ListOfAthletes;
}

bool RunningProfile::updateAthlete(Athlete updatedAthlete)
{
    for (int i = 0; i < ListOfAthletes.size(); i++)
    {
        Athlete currentAthlete = ListOfAthletes.at(i);
        if (updatedAthlete.returnName() == currentAthlete.returnName())
        {
            ListOfAthletes.replace(i,updatedAthlete);
            return true;
        }
    }
    //No Athlete of this name was found
    return false;
}

RunningProfile::~RunningProfile()
{
    //Destructor
}

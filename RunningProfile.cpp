#include "RunningProfile.h"

RunningProfile::RunningProfile()
{
    //Constructor
    profileName = "";
}

void RunningProfile::test()
{
    setName("Test Profile");

    Athlete Aaron;
    Aaron.setAthleteName("Aaron Martin");
    RunningEvent newEvent("400","1:11");
    Aaron.addToEventList(newEvent);
    RunningTime newTime;
    newTime = convertStringToTime("1:21");
    Athlete Jim;
    Jim.setAthleteName("Jim");
    newEvent.setTime(newTime);
    Jim.addToEventList(newEvent);

    addAthlete(Aaron);
    addAthlete(Jim);
}


void RunningProfile::setName(QString newName)
{
    profileName = newName;
}

QString RunningProfile::returnName()
{
    return profileName;
}

void RunningProfile::addAthlete(Athlete newAthlete)
{
    listOfAthletes.push_back(newAthlete);
}

void RunningProfile::removeAthlete(QString AthleteName)
{
    //Find Athlete
    for (unsigned int i = 0; i < listOfAthletes.size(); i++)
    {
        //Remove Athlete
        Athlete currentAthlete = listOfAthletes.at(i);
        if (AthleteName == currentAthlete.returnName())
        {
            //Once removed, update list
            for (unsigned int j = i; j < listOfAthletes.size(); j++)
            {
                listOfAthletes.at(j) = listOfAthletes.at(j+1);
            }
            listOfAthletes.pop_back();
            return;
        }
    }
}

Athlete RunningProfile::returnAthleteInformation(QString AthleteName)
{
    Athlete currentAthlete;
    for (unsigned int i = 0; i < listOfAthletes.size(); i++)
    {
        currentAthlete = listOfAthletes.at(i);
        if (AthleteName == currentAthlete.returnName())
        {
            return currentAthlete;
        }
    }
    //This is the fail statement
    currentAthlete.setAthleteName("FAILED");
    return currentAthlete;
}

std::vector<Athlete> RunningProfile::returnAllAthletes()
{
    return listOfAthletes;
}

bool RunningProfile::updateAthlete(Athlete updatedAthlete)
{
    for (unsigned int i = 0; i < listOfAthletes.size(); i++)
    {
        Athlete currentAthlete = listOfAthletes.at(i);
        if (updatedAthlete.returnName() == currentAthlete.returnName())
        {
            listOfAthletes.at(i) = updatedAthlete;
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

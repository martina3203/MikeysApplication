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

    if (writeToFile("") == true)
    {
        std::cout << "File Successfully written." << std::endl;
    }
    else
    {
        std::cout << "File was NOT written successfully." << std::endl;
    }

    //Reset Profile for read in
    setName("");

    if (readFromFile("Test Profile.txt") == true)
    {
        std::cout << "File Read Successfully." << std::endl;
        std::cout << "Profile Name: " << returnName();
    }
    else
    {
        std::cout << "File was NOT read successfully." << std::endl;
    }
}


void RunningProfile::setName(std::string newName)
{
    profileName = newName;
}

std::string RunningProfile::returnName()
{
    return profileName;
}

bool RunningProfile::writeToFile(std::string fileName)
{
    //File Format:
    //Profile Name
    //[Athlete] <EVENT NAME> == TIME
    //Adding events to the same line until Athlete is done and repeat for every Athlete
    std::ofstream newFile;
    if (fileName == "")
    {
        std::string newFileName = profileName + ".txt";
        newFile.open(newFileName.c_str());
    }
    else
    {
        newFile.open(fileName.c_str());
    }
    if (newFile.is_open() == true)
    {
        //Writes Profile Name
        newFile << profileName;
        //Then Every Athlete with their events
        for (unsigned int i = 0; i < listOfAthletes.size(); i++)
        {
            newFile << std::endl;
            Athlete currentAthlete = listOfAthletes.at(i);
            newFile << "[" << currentAthlete.returnName() << "] ";
            std::vector<RunningEvent> AthleteEvents = currentAthlete.returnRunningEvents();
            for (unsigned int j = 0; j < AthleteEvents.size(); j++)
            {
                RunningEvent currentEvent = AthleteEvents.at(j);
                RunningTime currentTime = currentEvent.returnTime();
                //Encases the name in arrows while the time is placed after the ==
                newFile << " <" << currentEvent.returnEventName() << ">" << "=" <<
                    currentTime.returnHours() << ":" << currentTime.returnMinutes() << ":" << currentTime.returnSeconds() << "." << currentTime.returnMiliseconds();
            }
        }
        newFile.close();
        return true;
    }
    else
    {
        newFile.close();
        return false;
    }
}

bool RunningProfile::readFromFile(std::string fileName)
{
    std::ifstream targetFile;
    targetFile.open(fileName.c_str());
    if (targetFile.is_open())
    {
        //Profile Name
        std::getline(targetFile,profileName);
        while(targetFile.eof() != true)
        {
            //Parses line by line
            std::string inputInformation;
            Athlete currentAthlete;
            getline(targetFile,inputInformation);
            for (unsigned int i = 0; i < inputInformation.size(); i++)
            {
                //Acquires name field
                if (inputInformation.at(i) == '[')
                {
                    std::string AthleteName = "";
                    for (unsigned int j = i+1; i < inputInformation.size(); j++)
                    {
                        //Signals end of name field
                        if (inputInformation.at(j) != ']')
                        {
                            AthleteName = AthleteName + inputInformation.at(j);
                        }
                        else
                        {
                            //Update iterator and break loop
                            if (AthleteName == "")
                            {
                                //this handles the case of an accidental hit of the newline character
                                break;
                            }
                            currentAthlete.setAthleteName(AthleteName);
                            i = j;
                            break;
                        }
                    }
                }
                //Acquires events and their respective times
                if (inputInformation.at(i) == '<')
                {
                    RunningEvent newEvent;
                    std::string eventName = "";
                    for (unsigned int j = i+1; i < inputInformation.size(); j++)
                    {
                        //Build Name
                        if (inputInformation.at(j) != '>')
                        {
                            eventName = eventName + inputInformation.at(j);
                        }
                        else
                        {
                            //Name completed, now acquire time for event
                            std::string stringTime = "";
                            newEvent.setName(eventName);
                            std::cout << eventName << std::endl;
                            for (unsigned int k = j+2; k < inputInformation.size(); k++)
                            {
                                if ((inputInformation.at(k) != ' ') && (k != inputInformation.size()-1))
                                {
                                    stringTime = stringTime + inputInformation.at(k);
                                }
                                else
                                {
                                    //Time finish, convert and load time, update iterator
                                    RunningTime eventTime = convertStringToTime(stringTime);
                                    std::cout << stringTime << std::endl;
                                    newEvent.setTime(eventTime);
                                    currentAthlete.addToEventList(newEvent);
                                    i = k + 1;
                                    break;
                                }

                            }
                        }

                    }
                }
            }
            listOfAthletes.push_back(currentAthlete);
        }
        targetFile.close();
        return true;
    }
    else
    {
        targetFile.close();
        return false;
    }
}

void RunningProfile::addAthlete(Athlete newAthlete)
{
    listOfAthletes.push_back(newAthlete);
}

void RunningProfile::removeAthlete(std::string AthleteName)
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

Athlete RunningProfile::returnAthleteInformation(std::string AthleteName)
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

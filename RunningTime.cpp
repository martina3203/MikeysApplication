#include "RunningTime.h"

/*
    Contains the RunningTime class. Purpose of this class is to store time intervals of any kind.
*/

RunningTime::RunningTime()
{
    //Constructor
    miliseconds = 0;
    seconds = 0;
    minutes = 0;
    hours = 0;
}

RunningTime::~RunningTime()
{
    //Destructor
}

int RunningTime::testFunction()
{
    //Test Output
    RunningTime testTime;
    testTime.setSeconds(02);
    testTime.setMinutes(56);
    testTime.setHours(3);
    testTime.setMiliseconds(5);
    std::cout << "Cout Ouput: ";
    std::cout << testTime << std::endl;

    //Testing optional Hour component
    testTime.setHours(0);
    std::cout << "Testing optional Hours segment: " << testTime << std::endl;

    //Testing optional Milisecond component
    testTime.setMiliseconds(0);
    std::cout << "Testing optional Miliseconds segment: " << testTime << std::endl;

    //Test Function Overloading
    RunningTime test1;
    RunningTime test2;
    //Comparison Testing
    if (test1 == test2)
    {
        std::cout << "Comparison: PASSED" << std::endl;
    }
    else
    {
        std::cout << "Comparison: FAILED" << std::endl;
    }
    //Inequality test
    test2.setSeconds(1);
    if (test1 != test2)
    {
        std::cout << "False Comparison: PASSED" << std::endl;
    }
    else
    {
        std::cout << "False Comparison: FAILED" << std::endl;
    }
    //Greater Than
    if (test2 > test1)
    {
        std::cout << "Greater Than: PASSED" << std::endl;
    }
    else
    {
        std::cout << "Greater Than: FAILED" << std::endl;
    }
    //Less Than
    if (test1 < test2)
    {
        std::cout << "Less Than: PASSED" << std::endl;
    }
    else
    {
        std::cout << "Less Than: FAILED" << std::endl;
    }

    //Testing Conversions of strings to times
    std::cout << convertStringToTime("0:01:2.45") << std::endl;
    std::cout << convertStringToTime("4:00:2.19") << std::endl;
    std::cout << convertStringToTime("02:14:19") << std::endl;
    std::cout << convertStringToTime("1:25") << std::endl;
    std::cout << convertStringToTime("16.5") << std::endl;
    std::cout << convertStringToTime("72.2") << std::endl;
    return 1;
}

void RunningTime::setMiliseconds(int newMili)
{
    int currentMSeconds = newMili;
    while (currentMSeconds >= 100)
    {
        seconds++;
        currentMSeconds = currentMSeconds - 100;
    }
    miliseconds = currentMSeconds;
}

void RunningTime::setSeconds(int newSeconds)
{
    //If the value is beyond 60
    int currentSeconds = newSeconds;
    while (currentSeconds >= 60)
    {
        //increment minutes, subtract 60 to continue to a readable format
        minutes++;
        currentSeconds = currentSeconds - 60;
    }
    seconds = currentSeconds;
}

void RunningTime::setMinutes(int newMinutes)
{
    //If the value is beyond 60
    int currentMinutes = newMinutes;
    while (currentMinutes >= 60)
    {
        //increment hours, subtract 60 to continue to a readable format
        hours++;
        currentMinutes = currentMinutes - 60;
    }
    minutes = currentMinutes;
}

void RunningTime::setHours(int newHours)
{
    hours = newHours;
}

int RunningTime::returnMiliseconds()
{
    return miliseconds;
}

int RunningTime::returnSeconds()
{
    return seconds;
}

int RunningTime::returnMinutes()
{
    return minutes;
}

int RunningTime::returnHours()
{
    return hours;
}

bool RunningTime::operator == (RunningTime anotheRunningTime)
{
    if (this -> returnMiliseconds() == anotheRunningTime.returnMiliseconds())
    {
        if (this -> returnSeconds() == anotheRunningTime.returnSeconds())
        {
            if (this -> returnMinutes() == anotheRunningTime.returnMinutes())
            {
                if (this -> returnHours() == anotheRunningTime.returnHours())
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool RunningTime::operator != (RunningTime anotheRunningTime)
{
    if (this -> returnMiliseconds() != anotheRunningTime.returnMiliseconds() ||
        this -> returnSeconds() != anotheRunningTime.returnSeconds() ||
        this -> returnMinutes() != anotheRunningTime.returnMinutes() ||
        this -> returnHours() != anotheRunningTime.returnHours())
    {
        return true;
    }
    return false;
}

bool RunningTime::operator < (RunningTime anotheRunningTime)
{
    if (this -> returnMiliseconds() < anotheRunningTime.returnMiliseconds())
    {
        return true;
    }
    if (this -> returnHours() < anotheRunningTime.returnHours())
    {
        return true;
    }
    if (this -> returnMinutes() < anotheRunningTime.returnMinutes())
    {
        return true;
    }
    if (this -> returnSeconds() < anotheRunningTime.returnSeconds())
    {
        return true;
    }
    //Else, false
    return false;
}

bool RunningTime::operator > (RunningTime anotheRunningTime)
{
    if (this -> returnMiliseconds() > anotheRunningTime.returnMiliseconds())
    {
        return true;
    }
    if (this -> returnHours() > anotheRunningTime.returnHours())
    {
        return true;
    }
    if (this -> returnMinutes() > anotheRunningTime.returnMinutes())
    {
        return true;
    }
    if (this -> returnSeconds() > anotheRunningTime.returnSeconds())
    {
        return true;
    }
    //Else, false
    return false;
}

std::ostream& operator << (std::ostream& Output,RunningTime theTime)
{
    //Builds a cout statement for the Time class
    //Hours component which is optional
    if (theTime.returnHours() != 0)
    {
        Output.width(2);
        Output.fill('0');
        Output << theTime.returnHours() << ":";
    }
    Output.width(2);
    Output.fill('0');
    //Minutes component
    Output << theTime.returnMinutes()<< ":";
    Output.width(2);
    Output.fill('0');
    //Seconds component
    Output << theTime.returnSeconds();
    //Miliseconds portion, which is also optional
    if (theTime.returnMiliseconds() != 0)
    {
        Output << ".";
        Output.width(2);
        Output.fill('0');
        Output << theTime.returnMiliseconds();
    }
    return Output;
}

RunningTime convertStringToTime(QString timeString)
{
    //Time shall be given in a format where it contains all 00:00:00.0 or some of these components
    //This function will parse through the strings and study the format for it and construct a RunningTime object
    //that contains the given information
    //Information is gathered in segments between each of the different punctation marks
    RunningTime convertedTime;
    QString timeSegment;
    int colonCounter = 0;
    bool periodFound = false;
    for (int i = 0; i < timeString.size(); i++)
    {
        if (timeString.at(i) == ':')
        {
            colonCounter++;
        }
        else if (timeString.at(i) == '.')
        {
            periodFound = true;
        }
    }
    unsigned int currentPosition = 0;
    int convertedNumber;
    //Dealing with a time in hours
    if (colonCounter == 2)
    {
        timeSegment = "";
        //Acquires Hour Position
        while (timeString.at(currentPosition) != ':')
        {
            timeSegment = timeSegment + timeString.at(currentPosition);
            currentPosition++;
        }
        convertedNumber = timeSegment.toInt();
        convertedTime.setHours(convertedNumber);
        convertedNumber = 0;
    }
    //Now the Minutes position
    if (colonCounter >= 1)
    {
        if (currentPosition != 0)
        {
            currentPosition++;
        }
        timeSegment = "";
        while (timeString.at(currentPosition) != ':')
        {
            timeSegment = timeSegment + timeString.at(currentPosition);
            currentPosition++;
        }
        convertedNumber = timeSegment.toInt();
        convertedTime.setMinutes(convertedNumber);
        convertedNumber = 0;
    }
    if (colonCounter >= 0)
    {
        if (currentPosition != 0)
        {
            currentPosition++;
        }
        timeSegment = "";
        while ((timeString.at(currentPosition) != '.') && (currentPosition < (timeString.size()-1)))
        {
            timeSegment = timeSegment + timeString.at(currentPosition);
            currentPosition++;
        }
        timeSegment = timeSegment + timeString.at(currentPosition);
        convertedNumber = timeSegment.toInt();
        convertedTime.setSeconds(convertedNumber);
        convertedNumber = 0;
    }
    //We may have a significant milisecond value
    if (periodFound == true)
    {
        timeSegment = "";
        for (unsigned int i = (currentPosition+1); i < timeString.size(); i++)
        {
            timeSegment = timeSegment + timeString.at(i);
        }
        timeSegment = timeSegment + timeString.at(currentPosition);
        convertedNumber = timeSegment.toInt();
        convertedTime.setMiliseconds(convertedNumber);
    }
    //Otherwise it remains zero, by default
    return convertedTime;
}

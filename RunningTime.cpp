#include "RunningTime.h"

/*
    Contains the RunningTime class. Purpose of this class is to store time intervals of any kind.
*/

RunningTime::RunningTime()
{
    //Constructor
    Miliseconds = 0;
    Seconds = 0;
    Minutes = 0;
    Hours = 0;
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
    std::cout << "Testing optional MiliSeconds segment: " << testTime << std::endl;

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
        Seconds++;
        currentMSeconds = currentMSeconds - 100;
    }
    Miliseconds = currentMSeconds;
}

void RunningTime::setSeconds(int newSeconds)
{
    //If the value is beyond 60
    int currentSeconds = newSeconds;
    while (currentSeconds >= 60)
    {
        //increment Minutes, subtract 60 to continue to a readable format
        Minutes++;
        currentSeconds = currentSeconds - 60;
    }
    Seconds = currentSeconds;
}

void RunningTime::setMinutes(int newMinutes)
{
    //If the value is beyond 60
    int currentMinutes = newMinutes;
    while (currentMinutes >= 60)
    {
        //increment Hours, subtract 60 to continue to a readable format
        Hours++;
        currentMinutes = currentMinutes - 60;
    }
    Minutes = currentMinutes;
}

QString RunningTime::toString()
{
    QString returnString = "";
    QString hoursString = QString::number(Hours);
    QString minutesString = QString::number(Minutes);
    QString secondsString = QString::number(Seconds);
    QString milisecondsString = QString::number(Miliseconds);
    //Build strings
    //Omit certain fields if empty.
    if (Hours != 0)
    {
        if (Hours < 10)
        {
            returnString = "0";
        }
        returnString = hoursString + ":";
    }
    //Only omit if there if minutes is 0 and hours is 0
    if ((Minutes != 0) || (Hours != 0))
    {
        if (Minutes < 10)
        {
            returnString = returnString + "0";
        }
        returnString = returnString + minutesString + ":";
    }
    //Seconds field will always be included
    if (Seconds < 10)
    {
        returnString = returnString + "0";
    }
    returnString = returnString + secondsString;
    //Omit if zero
    if (Miliseconds != 0)
    {
        returnString = returnString + ".";
        if (Miliseconds < 10)
        {
            returnString = returnString + "0" + milisecondsString;
        }
        else
        {
            returnString = returnString + milisecondsString;
        }
    }
    return returnString;
}

void RunningTime::setHours(int newHours)
{
    Hours = newHours;
}

int RunningTime::returnMiliseconds()
{
    return Miliseconds;
}

int RunningTime::returnSeconds()
{
    return Seconds;
}

int RunningTime::returnMinutes()
{
    return Minutes;
}

int RunningTime::returnHours()
{
    return Hours;
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
    //MiliSeconds portion, which is also optional
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
    //First we parse to see how many colons and periods there are
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
    int currentPosition = 0;
    int convertedNumber;
    //Dealing with a time in Hours
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
        //Move to next position
        currentPosition++;
    }
    //Now the Minutes position
    if (colonCounter >= 1)
    {
        timeSegment = "";
        while (timeString.at(currentPosition) != ':')
        {
            timeSegment = timeSegment + timeString.at(currentPosition);
            currentPosition++;
        }
        convertedNumber = timeSegment.toInt();
        convertedTime.setMinutes(convertedNumber);
        convertedNumber = 0;
        //Move to next position
        currentPosition++;
    }
    if (colonCounter >= 0)
    {
        timeSegment = "";
        while ((timeString.at(currentPosition) != '.') && (currentPosition < (timeString.size()-1)))
        {
            timeSegment = timeSegment + timeString.at(currentPosition);
            currentPosition++;
        }
        convertedNumber = timeSegment.toInt();
        convertedTime.setSeconds(convertedNumber);
        convertedNumber = 0;
        //Move to next position, if one should exist
        currentPosition++;
    }
    //We may have a significant milisecond value
    if (periodFound == true)
    {
        timeSegment = "";
        for (int i = currentPosition; i < timeString.size(); i++)
        {
            timeSegment = timeSegment + timeString.at(i);
        }
        convertedNumber = timeSegment.toInt();
        convertedTime.setMiliseconds(convertedNumber);
    }
    //Otherwise it remains zero, by default
    return convertedTime;
}

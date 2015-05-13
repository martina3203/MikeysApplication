#include "Athlete.h"

Athlete::Athlete()
{
    //Constructor
    AthleteName = "";
}

Athlete::Athlete(QString newName = "")
{
    //Paramerterize Constructor
    AthleteName = newName;
}

void Athlete::test()
{
    //Create first event
    RunningEvent newEvent;
    newEvent.setName("400");
    RunningTime newTime;
    newTime.setSeconds(54);
    newEvent.setTime(newTime);
    //Add Second Event, same name
    eventList.push_back(newEvent);
    newTime.setSeconds(46);
    newEvent.setTime(newTime);
    eventList.push_back(newEvent);

    std::cout << "Current List." << std::endl;
    printEventList();
    //Clear List
    removeEvent(1);
    std::cout << "List after deletion." << std::endl;
    printEventList();

    clearEventList();
    //Attempt to print empty list
    printEventList();
}

QString Athlete::returnName()
{
    return AthleteName;
}

void Athlete::setAthleteName(QString newName)
{
    AthleteName = newName;
}

std::vector<RunningEvent> Athlete::returnRunningEvents()
{
    return eventList;
}

void Athlete::addToEventList(RunningEvent newEvent)
{
    eventList.push_back(newEvent);
    return;
}

bool Athlete::removeEvent(unsigned int position)
{
    if (position < eventList.size())
    {
        for (unsigned int i = position; i < eventList.size()-1; i++)
        {
            //Swaps down the line until we get to last position
            eventList.at(i) = eventList.at(i+1);
        }
        //Removes last position
        eventList.pop_back();
        return true;
    }
    //This occurs in the case of failure
    return false;
}

void Athlete::clearEventList()
{
    eventList.clear();
    return;
}

void Athlete::printEventList()
{
    if (eventList.size() != 0)
    {
        for (unsigned int i = 0; i < eventList.size(); i++)
        {
        }
    }
    else
    {
        std::cout << "Event List is Empty" << std::endl;
    }
}

Athlete::~Athlete()
{
    //Destructor
}

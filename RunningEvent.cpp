#include "RunningEvent.h"

RunningEvent::RunningEvent()
{
    EventName = "";
    AthleteID = 0;
}

RunningEvent::RunningEvent(QString event, QString time)
{
    EventName = event;
    EventTime = convertStringToTime(time);
}


QString RunningEvent::returnEventName()
{
    return EventName;
}

RunningTime RunningEvent::returnTime()
{
    return EventTime;
}

int RunningEvent::returnID()
{
    return ID;
}

int RunningEvent::returnAthleteID()
{
    return AthleteID;
}

QDate RunningEvent::returnDate()
{
    return EventDate;
}

void RunningEvent::setName(QString newName)
{
    EventName = newName;
}

void RunningEvent::setTime(RunningTime newTime)
{
    EventTime = newTime;
}

void RunningEvent::setID(int newID)
{
    ID = newID;
}

void RunningEvent::setAthleteID(int newAthleteID)
{
    AthleteID = newAthleteID;
}

void RunningEvent::setDate(QDate newDate)
{
    EventDate = newDate;
}

RunningEvent::~RunningEvent()
{
    //dtor
}

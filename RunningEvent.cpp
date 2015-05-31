#include "RunningEvent.h"

RunningEvent::RunningEvent()
{
    EventName = "";
    theAthlete = Athlete();
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

RunningEvent::~RunningEvent()
{
    //dtor
}

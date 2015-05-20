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

void RunningEvent::setName(QString newName)
{
    EventName = newName;
}

void RunningEvent::setTime(RunningTime newTime)
{
    EventTime = newTime;
}

RunningEvent::~RunningEvent()
{
    //dtor
}

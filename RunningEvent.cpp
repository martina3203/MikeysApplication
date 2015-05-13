#include "RunningEvent.h"

RunningEvent::RunningEvent()
{
    eventName = "";
}

RunningEvent::RunningEvent(QString event, QString time)
{
    eventName = event;
    eventTime = convertStringToTime(time);
}


QString RunningEvent::returnEventName()
{
    return eventName;
}

RunningTime RunningEvent::returnTime()
{
    return eventTime;
}

void RunningEvent::setName(QString newName)
{
    eventName = newName;
}

void RunningEvent::setTime(RunningTime newTime)
{
    eventTime = newTime;
}

RunningEvent::~RunningEvent()
{
    //dtor
}

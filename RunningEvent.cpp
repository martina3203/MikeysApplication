#include "RunningEvent.h"

RunningEvent::RunningEvent()
{
    eventName = "";
}

RunningEvent::RunningEvent(std::string event, std::string time)
{
    eventName = event;
    eventTime = convertStringToTime(time);
}


std::string RunningEvent::returnEventName()
{
    return eventName;
}

RunningTime RunningEvent::returnTime()
{
    return eventTime;
}

void RunningEvent::setName(std::string newName)
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

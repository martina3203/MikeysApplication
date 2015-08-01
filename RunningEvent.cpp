#include "RunningEvent.h"

RunningEvent::RunningEvent()
{
    EventName = "";
    AthleteID = 0;
    ID = 0;
    EventOrderNumber = 0;
}

RunningEvent::RunningEvent(QString event, QString time)
{
    EventName = event;
    EventTime = convertStringToTime(time);
    ID = 0;
    EventOrderNumber = 0;
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

int RunningEvent::returnEventOrderNumber()
{
    return EventOrderNumber;
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

void RunningEvent::setEventOrderNumber(int newEventOrder)
{
    EventOrderNumber = newEventOrder;
}

void RunningEvent::setDate(QDate newDate)
{
    EventDate = newDate;
}

RunningEvent::~RunningEvent()
{
    //dtor
}

//Utility functions

void QuickSort(QList<RunningEvent> &list,int start,int finish)
{
    if (start < finish)
    {
        int pivot = QuickSortPartition(list,start,finish);
        QuickSort(list,start,pivot-1);
        QuickSort(list,pivot+1,finish);
    }
}

int QuickSortPartition(QList<RunningEvent> &list, int start, int finish)
{
    int divider = start;
    RunningEvent pivotEvent = list.at(finish);
    int pivotEventOrder = pivotEvent.returnEventOrderNumber();
    for (int i = start; i < finish; i++)
    {
        RunningEvent currentEvent = list.at(i);
        int currentEventOrder = currentEvent.returnEventOrderNumber();
        if (currentEventOrder < pivotEventOrder)
        {
            list.swap(i,divider);
            divider++;
        }
    }
    list.swap(divider,finish);
    return divider;
}

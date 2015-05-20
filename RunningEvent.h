#ifndef RunningEvent_H
#define RunningEvent_H

#include <string>
#include "RunningTime.h"
#include "Athlete.h"

class RunningEvent
{
    public:
        RunningEvent();
        RunningEvent(QString,QString);
        virtual ~RunningEvent();
        void setName(QString);
        void setTime(RunningTime);
        QString returnEventName();
        RunningTime returnTime();
    protected:
    private:
        QString EventName;
        int ID;
        Athlete theAthlete;
        RunningTime EventTime;
        //We need to incorporate a date
};

#endif // RunningEvent_H

#ifndef RunningEvent_H
#define RunningEvent_H

#include <string>
#include "RunningTime.h"

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
        QString eventName;
        RunningTime eventTime;

};

#endif // RunningEvent_H

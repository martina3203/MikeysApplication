#ifndef RunningEvent_H
#define RunningEvent_H

#include <string>
#include "RunningTime.h"

class RunningEvent
{
    public:
        RunningEvent();
        RunningEvent(std::string,std::string);
        virtual ~RunningEvent();
        void setName(std::string);
        void setTime(RunningTime);
        std::string returnEventName();
        RunningTime returnTime();
    protected:
    private:
        std::string eventName;
        RunningTime eventTime;

};

#endif // RunningEvent_H

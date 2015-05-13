#ifndef RunningTime_H
#define RunningTime_H

#include <iostream>
#include <sstream>

/*
    Contains the RunningTime class. Purpose of this class is to store time intervals of any kind.
*/


class RunningTime
{
    public:
        RunningTime();
        int testFunction();
        virtual ~RunningTime();
        void setMiliseconds(int);
        void setSeconds(int);
        void setMinutes(int);
        void setHours(int);
        int returnMiliseconds();
        int returnSeconds();
        int returnMinutes();
        int returnHours();
        bool operator ==(RunningTime);
        bool operator !=(RunningTime);
        bool operator <(RunningTime);
        bool operator >(RunningTime);
    protected:
    private:
        int miliseconds;
        int seconds;
        int minutes;
        int hours;
};

//Ostream for Time
std::ostream& operator << (std::ostream&,const RunningTime);

RunningTime convertStringToTime(std::string);

#endif // RunningTime_H

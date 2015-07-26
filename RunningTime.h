#ifndef RunningTime_H
#define RunningTime_H

#include <iostream>
#include <sstream>
#include <QString>
#include <QDebug>
#include "Athlete.h"

/*
    Contains the RunningTime class. Purpose of this class is to store time intervals of any kind.
*/


class RunningTime
{
    public:
        RunningTime();
        RunningTime(QString);
        int testFunction();
        virtual ~RunningTime();
        void setMiliseconds(int);
        void setSeconds(int);
        void setMinutes(int);
        void setHours(int);
        QString toString();
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
        int Miliseconds;
        int Seconds;
        int Minutes;
        int Hours;
};

//Ostream for Time
std::ostream& operator << (std::ostream&,const RunningTime);

RunningTime convertStringToTime(QString);

#endif // RunningTime_H

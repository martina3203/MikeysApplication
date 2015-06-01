#ifndef RunningEvent_H
#define RunningEvent_H

#include <QString>
#include <QDate>
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
        void setID(int);
        void setAthleteID(int);
        void setDate(QDate);
        QString returnEventName();
        RunningTime returnTime();
        int returnID();
        int returnAthleteID();
        QDate returnDate();
    protected:
    private:
        QString EventName;
        int ID;
        int AthleteID;
        RunningTime EventTime;
        QDate EventDate;
};

#endif // RunningEvent_H

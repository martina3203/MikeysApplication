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
        void setEventOrderNumber(int);
        void setAthleteID(int);
        void setDate(QDate);
        QString returnEventName();
        RunningTime returnTime();
        int returnID();
        int returnAthleteID();
        int returnEventOrderNumber();
        QDate returnDate();
    protected:
    private:
        QString EventName;
        int ID;
        int AthleteID;
        int EventOrderNumber;
        RunningTime EventTime;
        QDate EventDate;
};

//Sorts events based on their event order
void QuickSort(QList<RunningEvent>&,int,int);

int QuickSortPartition(QList<RunningEvent>&,int,int);

#endif // RunningEvent_H

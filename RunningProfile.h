#ifndef RunningProfile_H
#define RunningProfile_H

#include <QString>
#include <QList>
#include "Athlete.h"

class RunningProfile
{
    public:
        RunningProfile();
        void test();
        void setName(QString);
        void setID(int);
        QString returnName();
        int returnID();
        void addAthlete(Athlete);
        void updateAthleteList(QList<Athlete>);
        void removeAthlete(QString);
        QList<Athlete> returnAllAthletes();
        Athlete returnAthleteInformation(QString);
        bool updateAthlete(Athlete);
        virtual ~RunningProfile();
    protected:
    private:
        int IDNumber;
        QString ProfileName;
        QList<Athlete> ListOfAthletes;
};

QString convertAthleteListToString(QList<Athlete>);

#endif // RunningProfile_H

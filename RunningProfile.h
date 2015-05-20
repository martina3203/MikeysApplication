#ifndef RunningProfile_H
#define RunningProfile_H

#include <QString>
#include <vector>
#include <fstream>
#include "Athlete.h"

class RunningProfile
{
    public:
        RunningProfile();
        void test();
        void setName(QString);
        QString returnName();
        void addAthlete(Athlete);
        void removeAthlete(QString);
        std::vector<Athlete> returnAllAthletes();
        Athlete returnAthleteInformation(QString);
        bool updateAthlete(Athlete);
        void sortListAlphabetically();
        bool readFromFile(QString);
        bool writeToFile(QString fileName = "");
        void printProfile();
        virtual ~RunningProfile();
    protected:
    private:
        QString profileName;
        std::vector<Athlete> listOfAthletes;
};

#endif // RunningProfile_H

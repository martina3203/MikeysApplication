#ifndef RunningProfile_H
#define RunningProfile_H

#include <string>
#include <vector>
#include <fstream>
#include "Athlete.h"

class RunningProfile
{
    public:
        RunningProfile();
        void test();
        void setName(std::string);
        std::string returnName();
        void addAthlete(Athlete);
        void removeAthlete(std::string);
        std::vector<Athlete> returnAllAthletes();
        Athlete returnAthleteInformation(std::string);
        bool updateAthlete(Athlete);
        void sortListAlphabetically();
        void quickSort(int,int);
        bool readFromFile(std::string);
        bool writeToFile(std::string fileName = "");
        void printProfile();
        virtual ~RunningProfile();
    protected:
    private:
        std::string profileName;
        std::vector<Athlete> listOfAthletes;
};

#endif // RunningProfile_H

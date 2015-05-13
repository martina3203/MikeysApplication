#ifndef Athlete_H
#define Athlete_H

/*
    Contains Athlete Class function headers
    Athlete contains a name and any events associated with it.
*/


#include <string>
#include <vector>
#include "RunningEvent.h"

/*
    Contains header for the Athlete class, which contains a name of the Athlete and a list of events they run.
*/

class Athlete
{
    public:
        Athlete();
        Athlete(std::string);
        void test();
        virtual ~Athlete();
        std::string returnName();
        void setAthleteName(std::string);
        std::vector<RunningEvent> returnRunningEvents();
        void addToEventList(RunningEvent);
        bool removeEvent(unsigned int);
        void printEventList();
        void clearEventList();
    protected:
    private:
        std::string AthleteName;
        std::vector<RunningEvent> eventList;
};

#endif // Athlete_H

#ifndef Athlete_H
#define Athlete_H

/*
    Contains Athlete Class function headers
    Athlete contains a name and any events associated with it.
*/


#include <QString>
#include <vector>

/*
    Contains header for the Athlete class, which contains a name of the Athlete and a list of events they run.
*/

class Athlete
{
    public:
        Athlete();
        Athlete(QString,int);
        void test();
        virtual ~Athlete();
        QString returnName();
        int returnID();
        void setID(int);
        void setAthleteName(QString);
    protected:
    private:
        QString AthleteName;
        int ID;
};

#endif // Athlete_H

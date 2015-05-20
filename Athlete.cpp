#include "Athlete.h"

Athlete::Athlete()
{
    //Constructor
    AthleteName = "";
    ID = 0;
}

Athlete::Athlete(QString newName = "",int newID = 0)
{
    //Paramerterize Constructor
    AthleteName = newName;
    ID = newID;
}

void Athlete::test()
{

}

QString Athlete::returnName()
{
    return AthleteName;
}

int Athlete::returnID()
{
    return ID;
}

void Athlete::setID(int newID)
{
    ID = newID;
}

void Athlete::setAthleteName(QString newName)
{
    AthleteName = newName;
}

Athlete::~Athlete()
{
    //Destructor
}

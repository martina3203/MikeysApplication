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


//Utility Functions

//Quick Sort algorithm that uses middle element as the pivot
void QuickSort(QList<Athlete> &list,int start,int finish)
{
    if (start < finish)
    {
        int pivot = QuickSortPartition(list,start,finish);
        QuickSort(list,start,pivot-1);
        QuickSort(list,pivot+1,finish);
    }
}

int QuickSortPartition(QList<Athlete> &list,int start,int finish)
{
    int index = ((start + finish)/2);
    //Swap index with last position
    list.swap(index,(list.size()-1));
    int pivot = start;
    Athlete pivotAthlete = list.at(pivot);
    QString pivotName = pivotAthlete.returnName();
    for (int i = start; i < finish; i++)
    {
        Athlete currentAthlete = list.at(i);
        QString currentName = currentAthlete.returnName();
        if (AlphabeticallyFirst(pivotName,currentName))
        {
            list.swap(i,pivot);
            pivot++;
            pivotAthlete = list.at(pivot);
            pivotName = pivotAthlete.returnName();
        }
    }
    //Final swap and return
    list.swap(pivot,finish);
    return pivot;
}

#include "WorkoutWindow.h"

WorkoutWindow::WorkoutWindow(RunnerDatabase * databasePointer, RunningProfile selectedProfile,QDate selectedDate,
                             QList< QList<RunningEvent> > athleteEvents)
{
    setupUi(this);

    TheDatabase = databasePointer;
    CurrentProfile = selectedProfile;
    WorkoutDate = selectedDate;
    LoadedEvents = athleteEvents;

    //Update label to show current profile name
    ProfileNameLabel->setText(selectedProfile.returnName());
    //Update label to show current date
    WorkoutDateLabel->setText(selectedDate.toString(RunnerDatabase::DATE_FORMAT));

    //Find the model workout to be displayed
    findModelWorkout();
    UpdateWorkoutList();

    //Form connections
    connect(AddButton,SIGNAL(clicked()),this,SLOT(AddWorkout()));
    connect(buttonBox,SIGNAL(accepted()),this,SLOT(SaveChangesToDatabase()));
    connect(buttonBox,SIGNAL(rejected()),this,SLOT(close()));
    //Up and Down buttons
    connect(UpButton,SIGNAL(clicked(bool)),this,SLOT(ShiftListUp()));
    connect(DownButton,SIGNAL(clicked(bool)),this,SLOT(ShiftListDown()));
}

//Adds a workout to every athletes list
void WorkoutWindow::AddWorkout()
{
    QString workoutName = EventNameLineEdit->text();
    //Creating an entry for every athlete in their appropriate list
    QList<Athlete> athleteList = CurrentProfile.returnAllAthletes();
    //Set up event with base information
    RunningEvent newEvent;
    newEvent.setName(workoutName);
    newEvent.setDate(WorkoutDate);
    //Add it to every athlete event list
    for (int i = 0; i < LoadedEvents.size(); i++)
    {
        Athlete currentAthlete = athleteList.at(i);
        QList<RunningEvent> athleteEvents = LoadedEvents.at(i);
        newEvent.setAthleteID(currentAthlete.returnID());
        newEvent.setEventOrderNumber(athleteEvents.size());
        athleteEvents.append(newEvent);
        //now update the list for this athlete
        LoadedEvents.replace(i,athleteEvents);
    }

    //Update WorkoutList after change
    UpdateWorkoutList();
}

//Finds a workout that is listed for this group on this day
void WorkoutWindow::findModelWorkout()
{
    //We will parse through the current event list and find a workout that will serve for all athletes
    //If one should exist
    QList<RunningEvent> modelWorkoutList;
    for (int i = 0; i < LoadedEvents.size(); i++)
    {
        modelWorkoutList = LoadedEvents.at(i);
        if (modelWorkoutList.size() != 0)
        {
            //This is the model list
            break;
        }
    }
    if (modelWorkoutList.size() == 0)
    {
        //Nothing to do here so break
        return;
    }
    //We are gonna populate every entry with this list if they should need it
    QList<Athlete> athleteList = CurrentProfile.returnAllAthletes();
    for (int i = 0; i < athleteList.size(); i++)
    {
        Athlete currentAthlete = athleteList.at(i);
        int athleteID = currentAthlete.returnID();
        QList<RunningEvent> athleteEvents = LoadedEvents.at(i);
        if (athleteEvents.size() == 0)
        {
            //Make a new list and update it accordingly in the main container list
            for (int j = 0; j < modelWorkoutList.size(); j++)
            {
                RunningEvent currentEvent = modelWorkoutList.at(j);
                //Reset attributes of the current event
                currentEvent.setAthleteID(athleteID);
                currentEvent.setID(0);
                RunningTime defaultTime;
                currentEvent.setTime(defaultTime);
                modelWorkoutList.replace(j,currentEvent);
            }
            //Update it's list
            LoadedEvents.replace(i,modelWorkoutList);
        }
    }
}

void WorkoutWindow::ShiftListUp()
{
    ChangeListOrder(true);
}

void WorkoutWindow::ShiftListDown()
{
    ChangeListOrder(false);
}

void WorkoutWindow::ChangeListOrder(bool shiftUp)
{
    int currentIndex = WorkoutList->currentRow();
    int listSize = WorkoutList->count();
    int newIndex = 0;
    if ((shiftUp == true) && (currentIndex != 0))
    {
       newIndex = currentIndex - 1;
    }
    else if ((shiftUp == false) && (currentIndex != (listSize-1)))
    {
       newIndex = currentIndex + 1;
    }
    else
    {
        //Do nothing, invalid move
        return;
    }
    //Now we are going to update the list and the events
    //The list
    QListWidgetItem * currentItem = WorkoutList->item(currentIndex);
    QListWidgetItem * nextItem = WorkoutList->takeItem(newIndex);
    WorkoutList->insertItem(currentIndex, nextItem);
    WorkoutList->insertItem(newIndex, currentItem);

    //Now the events
    for (int i = 0; i < LoadedEvents.size(); i++)
    {
        QList<RunningEvent> currentAthleteEvents = LoadedEvents.at(i);
        //Change their event order
        RunningEvent firstEvent = currentAthleteEvents.at(currentIndex);
        firstEvent.setEventOrderNumber(newIndex);
        RunningEvent secondEvent = currentAthleteEvents.at(newIndex);
        secondEvent.setEventOrderNumber(currentIndex);
        //Change list order
        currentAthleteEvents.replace(currentIndex,secondEvent);
        currentAthleteEvents.replace(newIndex,firstEvent);
        //Save changes to the main list
        LoadedEvents.replace(i,currentAthleteEvents);
    }
}

//Updates list viewable to user
void WorkoutWindow::UpdateWorkoutList()
{
    //Clear list
    WorkoutList->clear();
    QList<RunningEvent> modelWorkoutList;
    for (int i = 0; i < LoadedEvents.size(); i++)
    {
        modelWorkoutList = LoadedEvents.at(i);
        if (modelWorkoutList.size() != 0)
        {
            //This is the model list
            break;
        }
    }
    //Update list to show the workout
    for (int i = 0; i < modelWorkoutList.size(); i++)
    {
        RunningEvent currentEvent = modelWorkoutList.at(i);
        QString eventName = currentEvent.returnEventName();
        WorkoutList->addItem(eventName);
    }
}

//Carries out changes to database
void WorkoutWindow::SaveChangesToDatabase()
{
    //Save all of the events that are available
    qDebug() << "Saving in Workout Window";
    for (int i = 0; i < LoadedEvents.size(); i++)
    {
        QList<RunningEvent> currentAthleteEvents = LoadedEvents.at(i);
        for (int j = 0; j < currentAthleteEvents.size(); j++)
        {
            RunningEvent currentEvent = currentAthleteEvents.at(j);
            int eventID = currentEvent.returnID();
            //If it doesn't exist in database, now add it
            if (eventID == 0)
            {
                if (!TheDatabase->addEvent(currentEvent))
                {
                    qDebug() << "Unable to add Event to Database from Workout Window";
                }
            }
            //Or update it's entry in the database
            else
            {
                if (!TheDatabase->updateEvent(currentEvent))
                {
                    qDebug() << "Unable to update Event in Database from Workout Window";
                }
            }
        }
    }

    //Remove all events that are meant to be removed from the Database
    for (int i = 0; i < EventsToBeRemoved.size(); i++)
    {
        RunningEvent currentEvent = EventsToBeRemoved.at(i);
        int eventID = currentEvent.returnAthleteID();
        if (eventID != 0)
        {
            if (!TheDatabase->removeEvent(eventID))
            {
                qDebug() << "Unable to remove event from the Workout Window";
            }
        }
    }
    close();
}

WorkoutWindow::~WorkoutWindow()
{
    //Destructor
}

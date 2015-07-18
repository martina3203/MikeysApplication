#include "WorkoutWindow.h"

WorkoutWindow::WorkoutWindow(RunnerDatabase * databasePointer, RunningProfile selectedProfile,QDate selectedDate)
{
    setupUi(this);

    TheDatabase = databasePointer;
    CurrentProfile = selectedProfile;
    WorkoutDate = selectedDate;

    //Update label to show current profile name
    ProfileNameLabel->setText(selectedProfile.returnName());
    //Update label to show current date
    WorkoutDateLabel->setText(selectedDate.toString(RunnerDatabase::DATE_FORMAT));

    //Form connections
    connect(buttonBox,SIGNAL(accepted()),this,SLOT(AddWorkoutToDatabase()));
}

//Function combines current settings to create a workout entry in the database
void WorkoutWindow::AddWorkoutToDatabase()
{
    QString workoutName = EventNameLineEdit->text();
    //Creating an entry for every athlete
    QList<Athlete> athleteList = CurrentProfile.returnAllAthletes();
    for (int i = 0; i < athleteList.size(); i++)
    {
        Athlete currentAthlete = athleteList.at(i);
        RunningEvent newEvent;
        //Set all attributes
        newEvent.setName(workoutName);
        newEvent.setAthleteID(currentAthlete.returnID());
        newEvent.setDate(WorkoutDate);
        //Add to Database
        if ((TheDatabase->addEvent(newEvent)) == 0)
        {
            qDebug() << "Failed to add event to Database in Workout Window.";
        }
    }
}

WorkoutWindow::~WorkoutWindow()
{
    //Destructor
}

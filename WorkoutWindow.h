#ifndef WORKOUTWINDOW_H
#define WORKOUTWINDOW_H

#include "ui_WorkoutWindow.h"
#include "RunningProfile.h"
#include "RunnerDatabase.h"
#include <QDialog>
#include <QDate>

class WorkoutWindow : public QDialog, public Ui_WorkoutWindow
{
    Q_OBJECT

public:
    WorkoutWindow(RunnerDatabase*,RunningProfile,QDate,QList< QList<RunningEvent> >);
    void findModelWorkout();
    ~WorkoutWindow();

public slots:
    void AddWorkout();
    void UpdateWorkoutList();
    void SaveChangesToDatabase();

private:
    RunningProfile CurrentProfile;
    RunnerDatabase * TheDatabase;
    QDate WorkoutDate;
    QList< QList<RunningEvent> > LoadedEvents;
    QList<RunningEvent> EventsToBeRemoved;
};

#endif // WORKOUTWINDOW_H

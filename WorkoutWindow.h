#ifndef WORKOUTWINDOW_H
#define WORKOUTWINDOW_H

#include "ui_WorkoutWindow.h"
#include "RunningProfile.h"
#include "RunnerDatabase.h"
#include <QDialog>
#include <QDate>

class WorkoutWindow : public QDialog, public Ui_WorkoutWindow
{
public:
    WorkoutWindow(RunnerDatabase*,RunningProfile,QDate);
    void AddWorkoutToDatabase();
private:
    RunningProfile CurrentProfile;
    RunnerDatabase * TheDatabase;
    QDate WorkoutDate;
};

#endif // WORKOUTWINDOW_H

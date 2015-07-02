#ifndef WORKOUTWINDOW_H
#define WORKOUTWINDOW_H

#include "ui_WorkoutWindow.h"
#include "RunningProfile.h"
#include "RunnerDatabase.h"
#include <QDialog>

class WorkoutWindow : public QDialog, public Ui_WorkoutWindow
{
public:
    WorkoutWindow(RunnerDatabase*,RunningProfile);
private:
    RunningProfile CurrentProfile;
    RunnerDatabase * TheDatabase;

};

#endif // WORKOUTWINDOW_H

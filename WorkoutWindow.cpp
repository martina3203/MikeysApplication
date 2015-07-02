#include "WorkoutWindow.h"

WorkoutWindow::WorkoutWindow(RunnerDatabase * databasePointer, RunningProfile selectedProfile)
{
    setupUi(this);

    TheDatabase = databasePointer;
    CurrentProfile = selectedProfile;
}


#ifndef MainWindow_H
#define MainWindow_H

#include <QMainWindow>
#include <QCloseEvent>
#include "ProfileWindow.h"
#include "RunnerDatabase.h"
#include "WorkoutWindow.h"
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow, public Ui_MainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void loadProfiles();
    void loadAthleteEvents();

signals:

public slots:
    void openProfileManager();
    void openWorkoutManager();
    bool loadAthletesFromProfile();
    void closeEvent(QCloseEvent*);

private:
    RunnerDatabase * TheDatabase;
    QList<RunningProfile> ProfileListing;
};

#endif // MainWindow_H

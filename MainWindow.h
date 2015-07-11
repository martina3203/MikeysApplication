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
    bool loadEventsForAllAthletes();
    bool loadEventsForSelectedAthlete();

signals:

public slots:
    void openProfileManager();
    void openWorkoutManager();
    bool loadAthletesFromProfile();
    void loadEvents();
    void displayEventsForSelection();
    void closeEvent(QCloseEvent*);

private:
    RunnerDatabase * TheDatabase;
    RunningProfile CurrentProfile;
    QList<RunningProfile> ProfileListing;
    QList<QList<RunningEvent> > CurrentEventListing;
    //Default String for usage in showing all athletes on the Athlete List
    static const QString showAllAthleteString;
};

#endif // MainWindow_H

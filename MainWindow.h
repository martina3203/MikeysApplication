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
    bool displayEventsForAllAthletes();
    bool displayEventsForSelectedAthlete();
    void fillTable();
signals:

public slots:
    void loadAthletes();
    void loadEvents();
    void loadAthletesAndEvents();
    void openProfileManager();
    void openWorkoutManager();
    void displayEventsForSelection();
    void toggleChangesMade();
    void saveCurrentTable();
    void saveChangesToDatabase();
    void closeEvent(QCloseEvent*);

private:
    RunnerDatabase * TheDatabase;
    RunningProfile CurrentProfile;
    //List that contains required materials
    QList<RunningProfile> ProfileListing;
    QList<QList<RunningEvent> > CurrentEventListing;
    QStringList EventHeaderList;
    //Default String for usage in showing all athletes on the Athlete List
    static const QString showAllAthleteString;
    //Boolean that determines if changes were made
    bool ChangesMade;
};

#endif // MainWindow_H

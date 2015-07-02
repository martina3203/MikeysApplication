#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{   
    TheDatabase = NULL;

    //Setup designed UI
    setupUi(this);

    //Let's build a database
    TheDatabase = new RunnerDatabase;

    //Updates dateEdit to be today's date
    DateEdit->setDate(QDate::currentDate());

    //Update Profile Listing ComboBox
    loadProfiles();

    //Build connections between buttons
    connect(ActionEdit_Profiles,SIGNAL(triggered(bool)),this,SLOT(openProfileManager()));
    connect(WorkoutButton,SIGNAL(clicked(bool)),this,SLOT(openWorkoutManager()));

}

void MainWindow::loadProfiles()
{
    //Load Profiles to Window list
    ProfileListing = TheDatabase->returnAllProfiles();
    //Updating listing in drop down box
    SelectProfileComboBox->clear();
    for (int i = 0; i < ProfileListing.size(); i++)
    {
        RunningProfile currentProfile = ProfileListing.at(i);
        SelectProfileComboBox->addItem(currentProfile.returnName());
    }
}

void MainWindow::openProfileManager()
{
    //Create a subwindow to access additional features retaining to the management of presaved profiles
    //Will wait til window is closed before proceeding
    ProfileWindow profileWindow(this,TheDatabase);
    profileWindow.exec();
}

void MainWindow::openWorkoutManager()
{
    //Acquire the current profile selected
    RunningProfile currentProfile;
    //Open Workout window
    WorkoutWindow workoutWindow(TheDatabase,currentProfile);
    workoutWindow.exec();
}

void MainWindow::closeEvent(QCloseEvent* theEvent)
{
    theEvent -> accept();
}

MainWindow::~MainWindow()
{
    //Cleans up memory associated with database access object
    if (TheDatabase != NULL)
    {
        delete TheDatabase;
    }
}

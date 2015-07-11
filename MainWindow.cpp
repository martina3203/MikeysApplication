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

    //Update Profile Listing ComboBox and if there is a profile existing, load it.
    loadProfiles();
    loadAthletesFromProfile();

    //Build connections between buttons and list
    connect(ActionEdit_Profiles,SIGNAL(triggered(bool)),this,SLOT(openProfileManager()));
    connect(WorkoutButton,SIGNAL(clicked(bool)),this,SLOT(openWorkoutManager()));
    //Loads Profile/Athletes on selection
    connect(SelectProfileComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(loadAthletesFromProfile()));
    //Loads events corresponding to date and profile
    connect(SelectProfileComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(loadEvents()));
    //Loads Events for display from prepared list
    connect(AthleteList,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(displayEventsForSelection()));
}

void MainWindow::loadEvents()
{
    return;
}

void MainWindow::displayEventsForSelection()
{
    int index = AthleteList->currentRow();
    if (index == 0)
    {
        loadEventsForAllAthletes();
    }
    else
    {
        loadEventsForSelectedAthlete();
    }
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

bool MainWindow::loadAthletesFromProfile()
{
    //Given a selected profile, we shall populate the list to include the Athlete Names
    qDebug() << "Selected Profile has been changed.";
    int newIndex = SelectProfileComboBox->currentIndex();
    //Clear current list
    AthleteList->clear();
    if (newIndex != -1)
    {
        //Then repopulate
        RunningProfile currentProfile = ProfileListing.at(newIndex);
        QList<Athlete> profileAthleteList = currentProfile.returnAllAthletes();
        for (int i = 0; i < profileAthleteList.size(); i++)
        {
            Athlete currentAthlete = profileAthleteList.at(i);
            QString athleteName = currentAthlete.returnName();
            AthleteList->addItem(athleteName);
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool MainWindow::loadEventsForAllAthletes()
{
    //Compile a list of strings to be the Y-Axis with Athlete Names
    int currentProfileIndex = SelectProfileComboBox->currentIndex();
    RunningProfile currentProfile = ProfileListing.at(currentProfileIndex);
    QList<Athlete> profileAthletes = currentProfile.returnAllAthletes();
    QStringList nameList;
    int rowNumber = 0;
    for (int i = 0; i < profileAthletes.size(); i++)
    {
        Athlete currentAthlete = profileAthletes.at(i);
        rowNumber++;
        nameList << currentAthlete.returnName();
    }
    EntriesTable ->setRowCount(rowNumber);
    EntriesTable -> setVerticalHeaderLabels(nameList);
    return true;
}

bool MainWindow::loadEventsForSelectedAthlete()
{

    return true;
}

//These functions open relevant windows
void MainWindow::openProfileManager()
{
    //Create a subwindow to access additional features retaining to the management of presaved profiles
    //Will wait til window is closed before proceeding
    ProfileWindow profileWindow(this,TheDatabase);
    profileWindow.exec();
    //Then we update the profile list
    loadProfiles();
}

void MainWindow::openWorkoutManager()
{
    //Acquire the current profile selected
    RunningProfile currentProfile;
    int listPosition = SelectProfileComboBox->currentIndex();
    currentProfile = ProfileListing.at(listPosition);
    //Acquire selected date
    QDate selectedDate = DateEdit->date();
    //Open Workout window
    WorkoutWindow workoutWindow(TheDatabase,currentProfile,selectedDate);
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

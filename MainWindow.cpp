#include "MainWindow.h"


const QString MainWindow::showAllAthleteString = "Show all Athletes";


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
    if (ProfileListing.size() != 0)
    {
        CurrentProfile = ProfileListing.at(0);
    }
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
        CurrentProfile = ProfileListing.at(newIndex);
        QList<Athlete> profileAthleteList = CurrentProfile.returnAllAthletes();
        if (profileAthleteList.size() > 1)
        {
            //Add an item that will list all athlete results
            AthleteList->addItem(showAllAthleteString);
        }
        for (int i = 0; i < profileAthleteList.size(); i++)
        {
            Athlete currentAthlete = profileAthleteList.at(i);
            QString athleteName = currentAthlete.returnName();
            AthleteList->addItem(athleteName);
        }
        //Now let it default to the first item on the list and display
        if (profileAthleteList.size() > 0)
        {
            AthleteList->setCurrentRow(0);
            displayEventsForSelection();
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
    QList<Athlete> profileAthletes = CurrentProfile.returnAllAthletes();
    QStringList nameList;
    int rowNumber = 0;
    for (int i = 0; i < profileAthletes.size(); i++)
    {
        Athlete currentAthlete = profileAthletes.at(i);
        rowNumber++;
        nameList << currentAthlete.returnName();
    }
    EntriesTable -> setRowCount(rowNumber);
    EntriesTable -> setVerticalHeaderLabels(nameList);
    return true;
}

bool MainWindow::loadEventsForSelectedAthlete()
{
    //This will only display the events corresponding to a single athlete that is selected
    int index = AthleteList->currentRow();
    QList<Athlete> profileAthletes = CurrentProfile.returnAllAthletes();
    int athleteListSize = AthleteList->count();
    if (athleteListSize > profileAthletes.size())
    {
        //This corrects the indexing if there is an option of "Show All"
        index--;
    }
    Athlete currentAthlete = profileAthletes.at(index);
    //It takes a list so I gave it a list of one
    QStringList stringList;
    stringList << currentAthlete.returnName();
    EntriesTable -> setRowCount(1);
    EntriesTable -> setVerticalHeaderLabels(stringList);

    return true;
}

//This will load all of the events into memory for usage
void MainWindow::loadEvents()
{
    return;
}

//This will display the events as designated by the user
void MainWindow::displayEventsForSelection()
{
    QListWidgetItem * index = AthleteList->currentItem();
    QString currentText;
    if (index != NULL)
    {
        currentText = index->text();
    }
    else
    {
        return;
    }
    if (currentText == showAllAthleteString)
    {
        loadEventsForAllAthletes();
    }
    else
    {
        loadEventsForSelectedAthlete();
    }
}

//The following functions open relevant windows
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

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
        loadAthletesAndEvents();
    }

    //Build connections between buttons and list
    connect(ActionEdit_Profiles,SIGNAL(triggered(bool)),this,SLOT(openProfileManager()));
    connect(WorkoutButton,SIGNAL(clicked(bool)),this,SLOT(openWorkoutManager()));
    //Loads different events when the date is changed on a selected profile
    connect(DateEdit,SIGNAL(dateChanged(QDate)),this,SLOT(loadEvents()));
    //Loads Profile/Athletes and events on selection
    connect(SelectProfileComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(loadAthletesAndEvents()));
    //Loads Events for display from prepared list
    connect(AthleteList,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(displayEventsForSelection()));
}

//Loads profiles to viewed in the SelectProfileComboBox
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

//Loads Athletes to be viewed in the AthleteList
void MainWindow::loadAthletes()
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
        }
    }
}

//Loads Athletes and their corresponding events
void MainWindow::loadAthletesAndEvents()
{
    loadAthletes();
    loadEvents();
    displayEventsForSelection();
}

//Displays on the table the events for all athletes on a specified date.
bool MainWindow::displayEventsForAllAthletes()
{
    //Compile a list of strings to be the Y-Axis with Athlete Names
    QList<Athlete> profileAthletes = CurrentProfile.returnAllAthletes();
    QStringList nameList;
    int rowNumber = 0;
    //Gather size of list along with athlete names
    for (int i = 0; i < profileAthletes.size(); i++)
    {
        Athlete currentAthlete = profileAthletes.at(i);
        rowNumber++;
        nameList << currentAthlete.returnName();
    }
    EntriesTable -> setRowCount(rowNumber);
    EntriesTable -> setVerticalHeaderLabels(nameList);
    //Compile a list of events to be the X-Axis
    QList<RunningEvent> eventList;
    for (int i = 0; i < profileAthletes.size(); i++)
    {
        eventList = CurrentEventListing.at(i);
        if (eventList.size() != 0)
        {
            //use this list as a model for the athletes in this profile
            break;
        }
    }
        qDebug() << "Not loaded crash";
    if (eventList.size() != 0)
    {
        nameList.clear();
        int columnCount = 0;
        for (int i = 0; i < eventList.size(); i++)
        {
            RunningEvent currentEvent = eventList.at(i);
            columnCount++;
            nameList << currentEvent.returnEventName();
        }
        EntriesTable->setColumnCount(columnCount);
        EntriesTable->setHorizontalHeaderLabels(nameList);
    }
    else
    {
        qDebug() << "No events found. Will not update Y-axis.";
    }
    return true;
}

//Displays on the table the events for a specific athlete selected by the user on a specified date
bool MainWindow::displayEventsForSelectedAthlete()
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
    QDate selectedDate = DateEdit->date();
    QList<Athlete> currentAthletes = CurrentProfile.returnAllAthletes();
    CurrentEventListing = TheDatabase->findEventsForGivenAthletes(currentAthletes,selectedDate);
    if (CurrentEventListing.size() != currentAthletes.size())
    {
        for (int i = CurrentEventListing.size(); i < currentAthletes.size(); i++)
        {
            QList<RunningEvent> placeholderList;
            CurrentEventListing.append(placeholderList);
        }
    }
    return;
}

//This will display the events as designated by the user
void MainWindow::displayEventsForSelection()
{
    QListWidgetItem * index = AthleteList->currentItem();
    QString currentText;

    //Reset table
    EntriesTable->clear();
    EntriesTable->setRowCount(0);
    EntriesTable->setColumnCount(0);

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
        displayEventsForAllAthletes();
    }
    else
    {
        displayEventsForSelectedAthlete();
    }
}

//The following functions open/close relevant windows
void MainWindow::openProfileManager()
{
    //Create a subwindow to access additional features retaining to the management of presaved profiles
    //Will wait til window is closed before proceeding
    ProfileWindow profileWindow(this,TheDatabase);
    profileWindow.exec();
    //Then we update the profile list
    loadProfiles();
    //And if possible, the Athlete list
    if (ProfileListing.size() != 0)
    {
        CurrentProfile = ProfileListing.at(0);
        loadAthletesAndEvents();
    }
}

void MainWindow::openWorkoutManager()
{
    //Acquire the current profile selected
    RunningProfile currentProfile;
    int listPosition = SelectProfileComboBox->currentIndex();
    if (listPosition != -1)
    {
        currentProfile = ProfileListing.at(listPosition);
        //Acquire selected date
        QDate selectedDate = DateEdit->date();
        //Open Workout window
        WorkoutWindow workoutWindow(TheDatabase,currentProfile,selectedDate);
        workoutWindow.exec();
        //On return, reload the events
        loadEvents();
    }
    else
    {
        //Error Message
    }
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

#include "MainWindow.h"

//Default String used in the case of "Show All"
const QString MainWindow::showAllAthleteString = "Show all Athletes";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{   
    TheDatabase = NULL;
    ChangesMade = false;

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
    //Determines if changes were made and saves them
    connect(EntriesTable,SIGNAL(cellChanged(int,int)),this,SLOT(toggleChangesMade()));
    connect(SaveChangesButton,SIGNAL(clicked(bool)),this,SLOT(saveChangesToDatabase()));
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
    setupRowAndColumnHeaders();
    displayEventsForSelection();
}

void MainWindow::setupRowAndColumnHeaders()
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
    for (int i = 0; i < CurrentEventListing.size(); i++)
    {
        eventList = CurrentEventListing.at(i);
        if (eventList.size() != 0)
        {
            //use this list as a model for the athletes in this profile
            break;
        }
    }
    if (eventList.size() != 0)
    {
        //Sets up StringList for header names
        EventHeaderList.clear();
        int columnCount = 0;
        for (int i = 0; i < eventList.size(); i++)
        {
            RunningEvent currentEvent = eventList.at(i);
            columnCount++;
            EventHeaderList << currentEvent.returnEventName();
        }
        EntriesTable->setColumnCount(columnCount);
        EntriesTable->setHorizontalHeaderLabels(EventHeaderList);
    }
}


//Displays on the table the events for all athletes on a specified date.
bool MainWindow::displayEventsForAllAthletes()
{
    int rows = EntriesTable->rowCount();
    for (int i = 0; i < rows; i++)
    {
        EntriesTable->showRow(i);
    }
    return true;
}

//Displays on the table the events for a specific athlete selected by the user on a specified date
bool MainWindow::displayEventsForSelectedAthlete()
{
    int athleteListSize = AthleteList->count();
    int rowCount = EntriesTable->rowCount();
    //If the profile has more than one athlete
    if (athleteListSize > 1)
    {
        //The reason to subtract 1 is to account for the case of "Show All Athletes"
        //When compared to the actual AthleteList
        int AthleteListIndex = (AthleteList->currentRow())-1;
        //We are now going to hide all of the other athletes from view
        for (int i = 0; i < rowCount; i++)
        {
            //Hide it if it's not the selected item
            if (i != AthleteListIndex)
            {
                EntriesTable->hideRow(i);
            }
            else
            {
                EntriesTable->showRow(i);
            }
        }
    }
    return true;
}

//This will load all of the events into memory for usage
void MainWindow::loadEvents()
{
    QDate selectedDate = DateEdit->date();
    QList<Athlete> currentAthletes = CurrentProfile.returnAllAthletes();
    CurrentEventListing = TheDatabase->findEventsForGivenAthletes(currentAthletes,selectedDate);
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
        displayEventsForAllAthletes();
    }
    else
    {
        displayEventsForSelectedAthlete();
    }
}

//Fills table with known entires from loaded event list and athletes
void MainWindow::fillTable()
{
    int columnNumber = EntriesTable->columnCount();
    //For each Athlete and their list
    for (int i = 0; i < CurrentEventListing.size(); i++)
    {
        //Load current list and populate every field for this athlete with some type of value
        QList<RunningEvent> currentAthleteEvents = CurrentEventListing.at(i);
        for (int j = 0; j < columnNumber; j++)
        {
            QString QStringTime;
            RunningTime eventTime;
            //If this event is listed and is in the right order
            if (j < currentAthleteEvents.size())
            {
                RunningEvent currentEvent = currentAthleteEvents.at(j);
                eventTime = currentEvent.returnTime();
            }
            //Else it will default to a value of 0 which will still be displayed
            //Create and add this entry to table
            QStringTime = eventTime.toString();
            QTableWidgetItem * newTableItem = new QTableWidgetItem(QStringTime);
            EntriesTable->setItem(i,j,newTableItem);
        }
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

//Saves the table for the current viewing session but NOT in the database
void MainWindow::saveCurrentTable()
{

}

//Saves all the changes to the Database
void MainWindow::saveChangesToDatabase()
{
    if (ChangesMade == true)
    {
        qDebug() << "Commence Saving";
        ChangesMade = false;
        SaveChangesButton->setEnabled(false);
    }
}

void MainWindow::toggleChangesMade()
{
    ChangesMade = true;
    //Enable Save Button
    SaveChangesButton->setEnabled(true);
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

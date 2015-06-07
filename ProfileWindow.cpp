#include "ProfileWindow.h"

ProfileWindow::ProfileWindow(QWidget *parent, RunnerDatabase * databaseAccess)
    : QDialog(parent)
{
    //Sets up window UI
    setupUi(this);
    TheDatabase = NULL;
    LoadedProfileIndex = 0;

    //Add profile names to first list
    loadProfilesToList();
    //Grab pointer to Database Access Object
    TheDatabase = databaseAccess;

    //Form Connections for buttons
    connect(ProfileList,SIGNAL(itemPressed(QListWidgetItem*)),this,SLOT(showSelectedProfileInfo()));
    connect(ProfileAddButton,SIGNAL(clicked()),this,SLOT(addNewProfile()));
    connect(ProfileRemoveButton,SIGNAL(clicked()),this,SLOT(removeProfile()));
    connect(AthleteAddButton,SIGNAL(clicked()),this,SLOT(addNewAthlete()));
    connect(AthleteRemoveButton,SIGNAL(clicked()),this,SLOT(removeAthlete()));
    connect(ButtonBox,SIGNAL(accepted()),this,SLOT(closeAndSave()));
}

void ProfileWindow::loadProfilesToList()
{
    //Remove anything that might already in the list
    ProfileList->clear();
    LoadedProfileList = TheDatabase->returnAllProfiles();
    //Add profiles to first list
    for (int i = 0; i < LoadedProfileList.size(); i++)
    {
        RunningProfile currentProfile = LoadedProfileList.at(i);
        QString currentProfileName = currentProfile.returnName();
        //Add to display list
        ProfileList -> addItem(currentProfileName);
    }
}

void ProfileWindow::addNewProfile()
{
    QString stringFromLineEdit = ProfileLineEdit->text();
    QString EmptyStringCheck = stringFromLineEdit;
    EmptyStringCheck.remove(' ');
    //If the string is not empty
    if ((EmptyStringCheck != ""))
    {
        //Take the string and build a profile out of it
        RunningProfile newProfile;
        newProfile.setName(stringFromLineEdit);
        //Add it to the list
        LoadedProfileList.append(newProfile);
        updateProfileList();
        return;
    }
    else
    {
        //Display empty string message
        return;
    }
}

void ProfileWindow::addNewAthlete()
{
    LoadedProfileIndex = ProfileList -> currentRow();
    RunningProfile currentProfile = LoadedProfileList.at(LoadedProfileIndex);
    QString stringFromLineEdit = AthleteLineEdit->text();
    QString EmptyStringCheck = stringFromLineEdit;
    EmptyStringCheck.remove(' ');
    //If the string is not empty
    if ((EmptyStringCheck != ""))
    {
        Athlete newAthlete;
        newAthlete.setAthleteName(stringFromLineEdit);
        currentProfile.addAthlete(newAthlete);
        //Now update the profile back to the list
        LoadedProfileList.replace(LoadedProfileIndex,currentProfile);
        //We are not adding him to the database though.
        //We will ask that the user wants to save his changes first.
        return;
    }
    else
    {
        //Display empty string message
        qDebug() << "Empty String";
        return;
    }
}

void ProfileWindow::removeProfile()
{
    //Find this profile and delete it from the database
    LoadedProfileIndex = ProfileList->currentRow();
    LoadedProfileList.removeAt(LoadedProfileIndex);
    //Deletes all selected items from the list and reloads list
    updateProfileList();
}

void ProfileWindow::removeAthlete()
{
    int athletePosition = AthleteList->currentRow();
    RunningProfile currentProfile = LoadedProfileList.at(LoadedProfileIndex);
    QList<Athlete> loadedAthleteList = currentProfile.returnAllAthletes();
    //Remove from the associated profile
    loadedAthleteList.removeAt(athletePosition);
    currentProfile.updateAthleteList(loadedAthleteList);
    //Now we are gonna update the profile in the list
    LoadedProfileList.replace(LoadedProfileIndex,currentProfile);
    //Update the Athlete List after the changes
    //Write to database later
    showSelectedProfileInfo();
}

void ProfileWindow::showSelectedProfileInfo()
{
    //When a profile is clicked, it will show all of the athletes associated with it
    LoadedProfileIndex = ProfileList->currentRow();
    RunningProfile currentProfile = LoadedProfileList.at(LoadedProfileIndex);
    //Clear the athlete list
    AthleteList->clear();
    //Now load all of the associated Athletes
    QList<Athlete> loadedAthleteList = currentProfile.returnAllAthletes();
    for (int i = 0; i < loadedAthleteList.size(); i++)
    {
        Athlete currentAthlete = loadedAthleteList.at(i);
        QString athleteName = currentAthlete.returnName();
        AthleteList->addItem(athleteName);
    }
}

void ProfileWindow::closeAndSave()
{

}

void ProfileWindow::updateProfileList()
{
    for (int i = 0; i < LoadedProfileList.size(); i++)
    {
        RunningProfile currentProfile = LoadedProfileList.at(i);
        QString currentProfileName = currentProfile.returnName();
        //Add to display list
        ProfileList -> addItem(currentProfileName);
    }
}

ProfileWindow::~ProfileWindow()
{
    //Destructor
}

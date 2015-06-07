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
    //Remove anything that might already list in the list
    ProfileList->clear();
    QList<RunningProfile> profileList = TheDatabase->returnAllProfiles();
    //Add profiles to first list
    for (int i = 0; i < profileList.size(); i++)
    {
        RunningProfile currentProfile = profileList.at(i);
        QString currentProfileName = currentProfile.returnName();
        //Add to display list
        ProfileList -> addItem(currentProfileName);
        //And finally to the LoadedProfileList
        LoadedProfileList.append(currentProfile);
    }
    //Then to save time we will preload all of the available running profile athletes
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
        //Add it to the database
        if (TheDatabase->addProfile(newProfile) == 0)
        {
            //Fail statement as the value should be it's ID in the database
            qDebug() << "Failed to add to Database from Profile Window.";
        }
        else
        {
            //Now update the list of profiles
            qDebug() << "Profiles should be loading.";
            loadProfilesToList();
        }
        return;
    }
    else
    {
        return;
    }
}

void ProfileWindow::addNewAthlete()
{
    QString stringFromLineEdit = AthleteLineEdit->text();
    QString stringFromLineEditWithoutSpaces = stringFromLineEdit.remove(' ');
    //If the string is not empty
    if ((stringFromLineEditWithoutSpaces != ""))
    {
        return;
    }
    else
    {
        return;
    }
}

void ProfileWindow::removeProfile()
{
    //Find this profile and delete it from the database
    int currentProfileSelected = ProfileList->currentRow();
    RunningProfile currentProfile = LoadedProfileList.at(currentProfileSelected);
    if (!(TheDatabase->removeProfile(currentProfile.returnID())))
    {
        //Fail statement
        qDebug() << "Failed to remove profile from Profile Window.";
    }
    //Deletes all selected items from the list and reloads list
    loadProfilesToList();
}

void ProfileWindow::removeAthlete()
{
    //Deletes all selected items
    qDeleteAll(AthleteList->selectedItems());
}

void ProfileWindow::showSelectedProfileInfo()
{
    //When a profile is clicked, it will show all of the athletes associated with it
}

void ProfileWindow::closeAndSave()
{

}

ProfileWindow::~ProfileWindow()
{
    //Destructor
}

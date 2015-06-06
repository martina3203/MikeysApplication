#include "ProfileWindow.h"

ProfileWindow::ProfileWindow(QWidget *parent, RunnerDatabase * databaseAccess)
    : QDialog(parent)
{
    //Sets up window UI
    setupUi(this);
    TheDatabase = NULL;

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
    QList<RunningProfile> profileList = TheDatabase->returnAllProfiles();
    //Add profiles to first list
    for (int i = 0; i < profileList.size(); i++)
    {
        RunningProfile currentProfile = profileList.at(i);
        QString currentProfileName = currentProfile.returnName();
        ProfileList -> addItem(currentProfileName);
    }
    //Then to save time we will preload all of the available running profile athletes
}

void ProfileWindow::addNewProfile()
{

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
    //Deletes all selected items
    qDeleteAll(ProfileList->selectedItems());
}

void ProfileWindow::removeAthlete()
{
    //Deletes all selected items
    qDeleteAll(AthleteList->selectedItems());
}

void ProfileWindow::showSelectedProfileInfo()
{

}

void ProfileWindow::closeAndSave()
{

}

ProfileWindow::~ProfileWindow()
{
    //Destructor
}

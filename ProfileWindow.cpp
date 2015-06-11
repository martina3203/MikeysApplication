#include "ProfileWindow.h"

ProfileWindow::ProfileWindow(QWidget *parent, RunnerDatabase * databaseAccess)
    : QDialog(parent)
{
    //Sets up window UI
    setupUi(this);
    TheDatabase = NULL;
    LoadedProfileIndex = 0;
    ChangesMade = false;

    //Grab pointer to Database Access Object
    TheDatabase = databaseAccess;

    //Add profile names to first list
    loadProfilesToList();

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
        ChangesMade = true;
        //Take the string and build a profile out of it
        RunningProfile newProfile;
        newProfile.setName(stringFromLineEdit);
        //Add it to the list
        LoadedProfileList.append(newProfile);
        updateProfileList();
        //Update the list view
        ProfileList->setCurrentRow(LoadedProfileList.size()-1);
        showSelectedProfileInfo();
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
        ChangesMade = true;
        Athlete newAthlete;
        newAthlete.setAthleteName(stringFromLineEdit);
        currentProfile.addAthlete(newAthlete);
        //Now update the profile back to the list
        LoadedProfileList.replace(LoadedProfileIndex,currentProfile);
        //We are not adding him to the database though.
        //We will ask that the user wants to save his changes first.
        //Update Athlete list
        showSelectedProfileInfo();
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
    ChangesMade = true;
    //Find this profile and delete it from the database
    LoadedProfileIndex = ProfileList->currentRow();
    //Acquire a copy of the Profile to be removed in the database later
    RunningProfile currentProfile = LoadedProfileList.at(LoadedProfileIndex);
    RemovedProfiles.append(currentProfile);
    //Remove from current list
    LoadedProfileList.removeAt(LoadedProfileIndex);
    //Deletes all selected items from the list and reloads list
    updateProfileList();
}

void ProfileWindow::removeAthlete()
{
    ChangesMade = true;
    int athletePosition = AthleteList->currentRow();
    RunningProfile currentProfile = LoadedProfileList.at(LoadedProfileIndex);
    QList<Athlete> loadedAthleteList = currentProfile.returnAllAthletes();

    //Acquire copy of athlete to be removed from the database
    Athlete currentAthlete = loadedAthleteList.at(athletePosition);
    RemovedAthletes.append(currentAthlete);
    //Remove from the associated profile
    loadedAthleteList.removeAt(athletePosition);
    currentProfile.updateAthleteList(loadedAthleteList);

    //Now we are gonna update the profile in the list
    LoadedProfileList.replace(LoadedProfileIndex,currentProfile);
    //Update the Athlete List after the changes
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
    //This is where we commit the changes to the Database, if needed
    if (ChangesMade)
    {
        //Set up a message box to ensure the user wants to make changes
        QMessageBox saveAlert;
        saveAlert.setText("Are you sure you wish to save your changes?");
        saveAlert.setInformativeText("You can't blame A-A-Ron if you mess up.");
        saveAlert.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
        saveAlert.setDefaultButton(QMessageBox::Cancel);
        int returnValue = saveAlert.exec();
        //If they want to save, else just return
        if (returnValue == QMessageBox::Save)
        {
            SaveChangesToDatabase();
            //Now we just close the window
            this->close();
        }
        else
        {
            return;
        }
    }
    else
    {
        //Simply close the window as no database interaction has to be carried out
        this->close();
    }
}

void ProfileWindow::SaveChangesToDatabase()
{
    //Add and update profiles accordingly
    for (int i = 0; i < LoadedProfileList.size(); i++)
    {
        RunningProfile currentProfile = LoadedProfileList.at(i);
        //We will need to add new athletes if they do not already exist in the database
        QList<Athlete> profileAthleteList = currentProfile.returnAllAthletes();
        for (int j = 0; j < profileAthleteList.size(); j++)
        {
            Athlete currentAthlete = profileAthleteList.at(j);
            //IF there is no ID for it, add it to database
            if (currentAthlete.returnID() == 0)
            {
                //Add accordingly
                if (TheDatabase->addAthlete(currentAthlete) == 0)
                {
                    qDebug() << "Failed to add new athlete from Profile Window while saving.";
                }
            }
            //Update it's value in the list
            profileAthleteList.replace(j,currentAthlete);
        }
        //Replace the list with a list of valid athletes with correct IDs
        currentProfile.updateAthleteList(profileAthleteList);

        //Finally, carry out the addition/update
        if (currentProfile.returnID() == 0)
        {
            //This needs to be added to the database
            if (!TheDatabase->addProfile(currentProfile))
            {
                qDebug() << "Failed to add Profile to Database from Profile Window";
            }
        }
        else if (!TheDatabase->updateProfile(currentProfile))
        {
            qDebug() << "Failed to update Profile in Database from Profile Window.";
        }
    }

    //Remove any profiles that have been removed
    for (int i = 0; i < RemovedProfiles.size(); i++)
    {
        RunningProfile currentProfile = RemovedProfiles.at(i);
        if (!TheDatabase->removeProfile(currentProfile.returnID()))
        {
            qDebug() << "Failed to remove Profile in Database from Profile Window.";
        }
    }

    //Remove any Athletes that have been removed from the database
    for (int i = 0; i < RemovedAthletes.size(); i++)
    {
        Athlete currentAthlete = RemovedAthletes.at(i);
        //If the value is non-zero, it has an entry in the database.
        //Else we need not worry about it
        if (currentAthlete.returnID() != 0)
        {
            if (!TheDatabase->removeAthlete(currentAthlete.returnID()))
            {
                qDebug() << "Failed to remove Athlete in Database from Profile Window.";
            }
        }
    }
}

void ProfileWindow::updateProfileList()
{
    ProfileList->clear();
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

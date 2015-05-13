#include "ProfileWindow.h"

ProfileWindow::ProfileWindow(QWidget *parent)
    : QDialog(parent)
{
    //Sets up window UI
    setupUi(this);
    //Read Profiles from Settings File
    settingsFile.readFile("settings.txt");
    if (settingsFile.returnFileLocations().size() == 0)
    {
        profileList -> addItem("NO PROFILES FOUND");
        return;
    }
    //Add profile names to first list
    loadProfilesToList();


    //Form Connections
    connect(profileList,SIGNAL(itemPressed(QListWidgetItem*)),this,SLOT(showSelectedProfileInfo()));
    connect(profileAddButton,SIGNAL(clicked()),this,SLOT(addNewProfile()));
    connect(profileRemoveButton,SIGNAL(clicked()),this,SLOT(removeProfile()));
    connect(AthleteAddButton,SIGNAL(clicked()),this,SLOT(addNewAthlete()));
    connect(AthleteRemoveButton,SIGNAL(clicked()),this,SLOT(removeAthlete()));
    connect(buttonBox,SIGNAL(accepted()),this,SLOT(closeAndSave()));
}

void ProfileWindow::loadProfilesToList()
{
    //Acquire list of files
    std::vector<std::string> filesToAccess = settingsFile.returnFileLocations();
    //Open and find names of files
    for (unsigned int i = 0; i < filesToAccess.size(); i++)
    {
        std::string currentFileName = filesToAccess.at(i);
        RunningProfile newProfile;
        //Reads from file
        if (newProfile.readFromFile(currentFileName) == true)
        {
            std::string profileName = newProfile.returnName();
            //Convert to Qstring
            QString newListElement = QString::fromStdString(profileName);
            //Add to list
            profileList -> addItem(newListElement);
            savedProfiles.push_back(newProfile);
        }
        else
        {
            //FAIL MESSAGE
        }
    }
}

void ProfileWindow::addNewProfile()
{
    QString stringFromLineEdit = profileLineEdit->text();
    if ((stringFromLineEdit != "") && (stringFromLineEdit != " "))
    {
        //Add to display list and data list
        profileList->addItem(stringFromLineEdit);
        RunningProfile newProfile;
        std::string profileName = stringFromLineEdit.toStdString();
        newProfile.setName(profileName);
        savedProfiles.push_back(newProfile);
        //Clear text box
        profileLineEdit -> clear();
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
    if ((stringFromLineEdit != "") && (stringFromLineEdit != " "))
    {
        //Now remove from the associated profile
        QString currentProfileQString = profileList-> currentItem() -> text();
        std::string currentProfile = currentProfileQString.toStdString();
        for (unsigned int i = 0; i < savedProfiles.size(); i++)
        {
            RunningProfile currentItemInVector = savedProfiles.at(i);
            if (currentProfile == currentItemInVector.returnName())
            {
                std::string newName = stringFromLineEdit.toStdString();
                Athlete newAthlete(newName);
                currentItemInVector.addAthlete(newAthlete);
                //Update profile listing
                savedProfiles.at(i) = currentItemInVector;
                //Show on list
                AthleteList->addItem(stringFromLineEdit);
                //Clear text box
                AthleteLineEdit -> clear();
            }
        }
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
    qDeleteAll(profileList->selectedItems());
}

void ProfileWindow::removeAthlete()
{
    //Deletes all selected items
    qDeleteAll(AthleteList->selectedItems());
}

void ProfileWindow::showSelectedProfileInfo()
{
    //Switches the viewing items in AthleteList based on selection in profileList
    AthleteList -> clear();
    QString selectedProfileName = profileList->currentItem() -> text();
    std::string stringName = selectedProfileName.toStdString();
    for (unsigned int i = 0; i < savedProfiles.size(); i++)
    {
        loadedProfile = savedProfiles.at(i);
        if (loadedProfile.returnName() == stringName)
        {
            //Found the profile
            break;
        }
    }
    //Add Athletes to list
    std::vector<Athlete> AthleteStorage = loadedProfile.returnAllAthletes();
    for (unsigned int i = 0; i < AthleteStorage.size(); i++)
    {
        Athlete currentAthlete = AthleteStorage.at(i);
        QString AthleteName = QString::fromStdString(currentAthlete.returnName());
        AthleteList -> addItem(AthleteName);
    }
}

void ProfileWindow::closeAndSave()
{
    settings newSettings;
    //Write new template files
    for (unsigned int i = 0; i < savedProfiles.size(); i++)
    {
        RunningProfile profileToWrite = savedProfiles.at(i);
        std::string newFileName = profileToWrite.returnName() + "TEMPLATE.txt";
        profileToWrite.writeToFile(newFileName);
        //Update settings file
        newSettings.addFileLocation(newFileName);
    }
    settingsFile = newSettings;
    settingsFile.writeFile();
}

ProfileWindow::~ProfileWindow()
{
    //Destructor
}

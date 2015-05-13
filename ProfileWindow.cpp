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

}

void ProfileWindow::addNewProfile()
{

}

void ProfileWindow::addNewAthlete()
{
    QString stringFromLineEdit = AthleteLineEdit->text();
    if ((stringFromLineEdit != "") && (stringFromLineEdit != " "))
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
    qDeleteAll(profileList->selectedItems());
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

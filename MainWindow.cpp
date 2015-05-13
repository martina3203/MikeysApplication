#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{   
    profileManager = NULL;

    //Setup designed UI
    setupUi(this);

    //Let's build a database


    //Updates dateEdit to be today's date
    dateEdit->setDate(QDate::currentDate());

    //Load settings file

    //Build connections between buttons
    connect(editProfileButton,SIGNAL(clicked()),this,SLOT(openProfileManager()));

}

void MainWindow::openProfileManager()
{
    //Create a subwindow to access additionalfeatures retaining to the management of presaved profiles
    if (profileManager == NULL)
    {
        profileManager = new ProfileWindow;
        profileManager -> show();
        profileManager -> raise();
        profileManager -> setModal(true);
        profileManager -> activateWindow();
    }
    else
    {
        profileManager -> show();
        profileManager -> raise();
        profileManager -> activateWindow();
    }
}

void MainWindow::closeEvent(QCloseEvent*)
{
    //Close Profile Manager if it is still open upon exit
    if (profileManager != NULL)
    {
        profileManager -> hide();
        profileManager -> close();
        delete profileManager;
    }
}

MainWindow::~MainWindow()
{
    //Cleans up memory taken by the Profile Manager
    if (profileManager != NULL)
    {
        delete profileManager;
    }
}

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{   
    profileManager = NULL;
    TheDatabase = NULL;

    //Setup designed UI
    setupUi(this);

    //Let's build a database
    TheDatabase = new RunnerDatabase;

    //Updates dateEdit to be today's date
    dateEdit->setDate(QDate::currentDate());

    //Build connections between buttons
    connect(editProfileButton,SIGNAL(clicked()),this,SLOT(openProfileManager()));

}

void MainWindow::openProfileManager()
{
    //Create a subwindow to access additionalfeatures retaining to the management of presaved profiles
    if (profileManager == NULL)
    {

        //Build Profile Window
        //Passing this as the parent will ensure that when the parent dies, the child dies
        profileManager = new ProfileWindow(this,TheDatabase);
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

void MainWindow::closeEvent(QCloseEvent* theEvent)
{
    theEvent -> accept();
}

MainWindow::~MainWindow()
{
    //Cleans up memory taken by the Profile Manager
    if (profileManager != NULL)
    {
        delete profileManager;
    }

    //Cleans up memory associated with database access object
    if (TheDatabase != NULL)
    {
        delete TheDatabase;
    }
}

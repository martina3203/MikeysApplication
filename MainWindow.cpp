#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{   
    TheDatabase = NULL;

    //Setup designed UI
    setupUi(this);

    //Let's build a database
    TheDatabase = new RunnerDatabase;

    //Updates dateEdit to be today's date
    dateEdit->setDate(QDate::currentDate());

    //Build connections between buttons
    connect(ActionEdit_Profiles,SIGNAL(triggered(bool)),this,SLOT(openProfileManager()));

}

void MainWindow::openProfileManager()
{
    //Create a subwindow to access additional features retaining to the management of presaved profiles
    //Will wait til window is closed before proceeding
    ProfileWindow profileWindow(this,TheDatabase);
    profileWindow.exec();
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

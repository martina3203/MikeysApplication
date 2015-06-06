#ifndef ProfileWindow_H
#define ProfileWindow_H

#include <QMainWindow>
#include <QDialog>
#include <QString>
#include "ui_ProfileWindow.h"
#include "RunnerDatabase.h"
#include "RunningProfile.h"

class ProfileWindow : public QDialog,public Ui_ProfileDialog
{
    Q_OBJECT

public:
    ProfileWindow(QWidget *parent = 0, RunnerDatabase * databaseAccess = NULL);
    void loadProfilesToList();
    ~ProfileWindow();

public slots:
    void addNewProfile();
    void addNewAthlete();
    void removeProfile();
    void removeAthlete();
    void showSelectedProfileInfo();
    void closeAndSave();

private:
    RunningProfile loadedProfile;
    RunnerDatabase * TheDatabase;

};

#endif // ProfileWindow_H

#ifndef ProfileWindow_H
#define ProfileWindow_H

#include <QMainWindow>
#include <QDialog>
#include <QString>
#include "ui_ProfileWindow.h"
#include "settings.h"
#include "RunningProfile.h"

class ProfileWindow : public QDialog,public Ui_profileDialog
{
    Q_OBJECT

public:
    ProfileWindow(QWidget *parent = 0);
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
    settings settingsFile;
    RunningProfile loadedProfile;
    std::vector<RunningProfile> savedProfiles;

};

#endif // ProfileWindow_H

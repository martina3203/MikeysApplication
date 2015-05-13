#ifndef MainWindow_H
#define MainWindow_H

#include <QMainWindow>
#include "ProfileWindow.h"
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow, public Ui_MainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:

public slots:
    void openProfileManager();
    void closeEvent(QCloseEvent*);

private:
    ProfileWindow * profileManager;
};

#endif // MainWindow_H

#include "MainWindow.h"
#include <QApplication>


//Standard main function to call forth the application
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

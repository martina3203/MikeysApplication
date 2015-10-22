#ifndef PRINTINGWINDOW_H
#define PRINTINGWINDOW_H

#include <QObject>
#include <QWidget>
#include "ui_PrintingWindow.h"

class PrintingWindow: public QDialog, public Ui_PrintingDialog
{
    Q_OBJECT

public:
    PrintingWindow();
};

#endif // PRINTINGWINDOW_H

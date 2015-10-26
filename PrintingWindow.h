#ifndef PRINTINGWINDOW_H
#define PRINTINGWINDOW_H

#include <QDialog>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include "ui_PrintingWindow.h"

class PrintingWindow : public QDialog, public Ui_PrintingDialog
{
    Q_OBJECT

public:
    PrintingWindow(QWidget *parent = 0);

public slots:

private:
    QPrinter thePrinter;
};

#endif // PRINTINGWINDOW_H

#ifndef PRINTINGWINDOW_H
#define PRINTINGWINDOW_H

#include <QDialog>
#include <QTableWidget>
#include <QPainter>
#include <QDebug>
#include <QDate>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include "ui_PrintingWindow.h"

class PrintingWindow : public QDialog, public Ui_PrintingDialog
{
    Q_OBJECT

public:
    PrintingWindow(QTableWidget * theTable, QDate workoutDate, QString profileName, QWidget *parent = 0 );
    void addTable();
    void configurePageSettings();

public slots:
    void executePrintJob();

private:
    QPrinter ThePrinter;
    QPainter ThePainter;
    QDate Date;
    QString ProfileName;
    QTableWidget * Table;
};

#endif // PRINTINGWINDOW_H

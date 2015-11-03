#include "PrintingWindow.h"

PrintingWindow::PrintingWindow(QTableWidget * theTable ,QWidget *parent) : QDialog(parent)
{
    //Constructor
    setupUi(this);
    Table = theTable;

    //Form Connections
    connect(buttonBox,SIGNAL(accepted()),this,SLOT(executePrintJob()));
}

void PrintingWindow::executePrintJob()
{
    //Intial setup
    configurePageSettings();

    //Add Text
    ThePainter.begin(&ThePrinter);
    ThePainter.drawText(10,10,"THE DATE");
    ThePainter.drawText(10,25,"THE PROFILE");

    //Add material to page
    addTable();

    ThePainter.end();

    //Bring up Print Dialog to select the proper printer
    QPrintDialog dialog(&ThePrinter, this);
            dialog.setWindowTitle(tr("Print Document"));
            if (dialog.exec() != QDialog::Accepted) {
                return;
            }
}

void PrintingWindow::addTable()
{
    //Draw Table
    Table->resizeRowsToContents();
    Table->resizeColumnsToContents();
    double xscale = ThePrinter.pageRect().width()/double(Table->width());
    double yscale = ThePrinter.pageRect().height()/double(Table->height());
    double scale = qMin(xscale, yscale);
    ThePainter.translate(ThePrinter.paperRect().x() + ThePrinter.pageRect().width()/2,
                     ThePrinter.paperRect().y() + ThePrinter.pageRect().height()/2);
    ThePainter.scale(scale, scale);
    ThePainter.translate(-width()/1.5, -height()/2);
    //Render to page
    Table->render(&ThePainter);
}

//Used to set the default attributes of the printer
void PrintingWindow::configurePageSettings()
{
    //Set default attributes of printer
    ThePrinter.setOrientation(QPrinter::Landscape);
    ThePrinter.setPaperSize(QPrinter::Legal);
    ThePrinter.setOutputFileName("printjob.pdf");
}

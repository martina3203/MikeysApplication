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

    //Add material to page
    addTable();

    //Bring up Print Dialog to select the proper printer
    QPrintDialog dialog(&ThePrinter, this);
            dialog.setWindowTitle(tr("Print Document"));
            if (dialog.exec() != QDialog::Accepted) {
                return;
            }
}

void PrintingWindow::addTable()
{
    //Set up Painter
    QPainter thePainter;
    thePainter.begin(&ThePrinter);
    Table->resizeRowsToContents();
    Table->resizeColumnsToContents();
    double xscale = ThePrinter.pageRect().width()/double(Table->width());
    double yscale = ThePrinter.pageRect().height()/double(Table->height());
    double scale = qMin(xscale, yscale);
    thePainter.translate(ThePrinter.paperRect().x() + ThePrinter.pageRect().width()/2,
                     ThePrinter.paperRect().y() + ThePrinter.pageRect().height()/2);
    thePainter.scale(scale, scale);
    thePainter.translate(-width()/1.5, -height()/2);

    //Render to page
    Table->render(&thePainter);

}

//Used to set the default attributes of the printer
void PrintingWindow::configurePageSettings()
{
    //Set default attributes of printer
    ThePrinter.setOrientation(QPrinter::Portrait);
    ThePrinter.setPaperSize(QPrinter::Legal);
    ThePrinter.setOutputFileName("printjob.pdf");
}

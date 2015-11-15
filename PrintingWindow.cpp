#include "PrintingWindow.h"

PrintingWindow::PrintingWindow(QTableWidget * theTable ,  QDate workoutDate, QString profileName, QWidget *parent) : QDialog(parent)
{
    //Constructor
    setupUi(this);
    Table = theTable;

    Date = workoutDate;
    ProfileName = profileName;

    //Form Connections
    connect(buttonBox,SIGNAL(accepted()),this,SLOT(executePrintJob()));
}

void PrintingWindow::executePrintJob()
{
    //Intial setup
    configurePageSettings();

    //Add Text
    ThePainter.begin(&ThePrinter);
    ThePainter.setFont(QFont("Arial",12));
    QString stringHolder = Date.toString("MM.dd.yyyy");
    ThePainter.drawText(10,10,stringHolder);
    stringHolder = ProfileName.toUpper();
    ThePainter.drawText(10,28,stringHolder);

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
    double xscale = ThePrinter.pageRect().width()/double(Table->width());
    double yscale = ThePrinter.pageRect().height()/double(Table->height());
    double scale = qMin(xscale, yscale);
    ThePainter.translate(ThePrinter.paperRect().x() + ThePrinter.pageRect().width()/8,
                         ThePrinter.paperRect().y() + ThePrinter.pageRect().height()/4);
    ThePainter.scale(scale, scale);
    ThePainter.translate(-width()/2, -height()/2);
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

#include "XPSDisplayWidget.h"
#include <QPixmap>
#include <QFileDialog>

XPSDisplayWidget::XPSDisplayWidget(QWidget *parent) :
	QWidget(parent)
{
	model_ = new XPSMapViewModel();

	numberOfScans_ = 0;


    // ToDo: Add Mplot widgets and plots, create a test map
    plotView_ = new MPlotWidget;
    plotView_->enableAntiAliasing(true);

    // Create plot and set up axes. These are all dummy values for testing
    plot_ = new MPlot;
    plot_->axisBottom()->setAxisNameFont(QFont("Helvetica", 6));
    plot_->axisBottom()->setTickLabelFont(QFont("Helvetica", 6));
    plot_->axisBottom()->setAxisName("x-axis");
    plot_->axisLeft()->setAxisNameFont(QFont("Helvetica", 6));
    plot_->axisLeft()->setTickLabelFont(QFont("Helvetica", 6));
    plot_->axisLeft()->setAxisName("y-axis");

    // Set the margins for the plot. Test values
    plot_->setMarginLeft(10);
    plot_->setMarginBottom(15);
    plot_->setMarginRight(2);
    plot_->setMarginTop(2);

    // FILL 2D data here using test values
    // This will be removed and replaced with data from XPSMap
    data2D_ = new MPlotSimpleImageData(1024, 1024);

    QVector<qreal> tempValue = QVector<qreal>(1024);
    for (int i = 0; i < 1024; i++)
        tempValue[i] = i;
    data2D_->setXValues(0, 1023, tempValue.data());
    data2D_->setYValues(0, 1023, tempValue.data());
    for(int yy=0; yy<1024; yy++) {
             for(int xx=0; xx<1024; xx++) {
                 qreal x = data2D_->x(xx);
                 qreal y = data2D_->y(yy);
                 qreal r2 = x*x + y*y;
                 data2D_->setZ(xx, yy, r2);
             }
         }

    MPlotImageBasic* plot2d = new MPlotImageBasic(data2D_);
    plot2d->setColorMap(MPlotColorMap::Jet);
    plot_->addItem(plot2d);

    // Enable autoscaling of both axes.
    plot_->axisScaleLeft()->setAutoScaleEnabled();
    plot_->axisScaleBottom()->setAutoScaleEnabled();

    // Enable some convenient zoom tools.
    plotView_->setPlot(plot_);
    plotView_->setMinimumHeight(450);
    plotView_->setMinimumWidth(600);

    // Set the number of ticks.  A balance between readability and being practical.
    plot_->axisBottom()->setTicks(3);
    plot_->axisTop()->setTicks(0);
    plot_->axisLeft()->setTicks(4);
    plot_->axisRight()->setTicks(0);

    // Set the autoscale constraints.
    plot_->axisScaleLeft()->setDataRangeConstraint(MPlotAxisRange(0, MPLOT_POS_INFINITY));

	scanListWidget_ = new QListWidget(this);
	addScanButton_ = new QPushButton("Add Scan", this);
	removeScanButton_ = new QPushButton("Remove Scan", this);
	createMapButton_ = new QPushButton("Create Map", this);

	mainLayout_ = new QHBoxLayout;
	buttonsLayout_ = new QHBoxLayout;
	panelLayout_ = new QVBoxLayout;
	mapLayout_ = new QVBoxLayout;

    mapLayout_->addWidget(plotView_);

	buttonsLayout_->addWidget(addScanButton_);
	buttonsLayout_->addWidget(removeScanButton_);

	panelLayout_->addWidget(scanListWidget_);
	panelLayout_->addLayout(buttonsLayout_);
	panelLayout_->addWidget(createMapButton_);

	mainLayout_->addLayout(panelLayout_);
	mainLayout_->addLayout(mapLayout_);

	setLayout(mainLayout_);

    connect(addScanButton_, SIGNAL(clicked()), this, SLOT(openFileDialog()));
    connect(this, SIGNAL(scanAdded()), this, SLOT(updateList()));
    connect(removeScanButton_, SIGNAL(clicked()), this, SLOT(removeScan()));



}

// ToDo: This looks better but need to set a size limit on the
// QLabels.  Also need some icon system of an X or a checkmark to show
// that an acceptable value has been put in.
void XPSDisplayWidget::openFileDialog(){

    // Add new scan dialog
    addScanDialog_ = new QDialog(this);

    // Should I move this to the constructor? Is it ok that
    // these widgets get created, and I assume destroyed, when the
    // window opens and closes?
    i0Label_ = new QLabel("I0: ");
    addPhotonEnergy_ = new QLineEdit("0");
    hvLabel_ = new QLabel("Photon Energy: ");
    addI0_ = new QLineEdit("0");
    findScanButton_ = new QPushButton("Find Scan");
    addFileName_ = new QLineEdit("File Selected");
    addScan_ = new QPushButton("Add this scan");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *subLayout = new QHBoxLayout;
    QVBoxLayout *paramLayout = new QVBoxLayout;

    QHBoxLayout *i0Layout = new QHBoxLayout;
    i0Layout->addWidget(i0Label_);
    i0Layout->addWidget(addI0_);

    QHBoxLayout *hvLayout = new QHBoxLayout;
    hvLayout->addWidget(hvLabel_);
    hvLayout->addWidget(addPhotonEnergy_);

    QHBoxLayout *fileLayout = new QHBoxLayout;
    fileLayout->addWidget(addFileName_);
    fileLayout->addWidget(findScanButton_);

    paramLayout->addLayout(i0Layout);
    paramLayout->addLayout(hvLayout);

    subLayout->addLayout(paramLayout);
    subLayout->addSpacing(100);
    subLayout->addWidget(addScan_);

    mainLayout->addLayout(fileLayout);
    mainLayout->addLayout(subLayout);

    addScanDialog_->setLayout(mainLayout);

    connect(findScanButton_, SIGNAL(clicked()), this, SLOT(findFile()));
    connect(addScan_, SIGNAL(clicked()), this, SLOT(addScan()));

    addScanDialog_->exec();


}

// Opens a new QFileDialog
// ToDo: grab XPS scan text file thats selected and add it to the XPSMap list of scans
void XPSDisplayWidget::findFile(){

    fileName_ = QFileDialog::getOpenFileName(this, tr("Add New Scan"),"/home/", tr("Text (*.txt)"));
    addFileName_->setText(fileName_);

}

void XPSDisplayWidget::addScan()
{
	//ToDo: add a check to make sure all values are valid/exist
	// This check should take place in the dialog and not here

	qreal hv_ = addPhotonEnergy_->text().toDouble();
	qreal i0_ = addI0_->text().toDouble();

	model_->loadScansFromFiles(i0_, hv_, fileName_);

	//update the list of files
	numberOfScans_++;
	emit scanAdded();
	addScanDialog_->close();
}

void XPSDisplayWidget::removeScan()
{
	//Remove scan from list widget
	scanListWidget_->takeItem(numberOfScans_-1);
	numberOfScans_--;

	//Remove scan from QList<XPS>
	// model needs ability to remove a scan

}


void XPSDisplayWidget::displayMap()
{
	//Send the XPSMap to the MPlot stuff

}

void XPSDisplayWidget::updateList()
{
	// Using a global variable to track number of scans for sole
	// purpose of knowing the index value of the top scan.
	// I could create a getter in the model to know the number of scans too
	scanListWidget_->addItem(model_->scanName(numberOfScans_-1));

}

#include "XPSDisplayWidget.h"
#include <QPixmap>
#include <QFileDialog>
#include <MPlot/MPlotTools.h>

XPSDisplayWidget::XPSDisplayWidget(QWidget *parent) :
	QWidget(parent)
{
	model_ = new XPSMapViewModel();

	numberOfScans_ = 0;

    batchAddScanDialog_ = 0;
    data2D_ = 0;
    plot2D_ = 0;

    plotView_ = new MPlotWidget;
	plotView_->enableAntiAliasing(true);

	// Create plot and set up axes. These are all dummy values for testing
	plot_ = new MPlot;
    plot_->axisBottom()->setAxisNameFont(QFont("Helvetica", 6));
    plot_->axisBottom()->setTickLabelFont(QFont("Helvetica", 6));
    plot_->axisBottom()->setAxisName("Kinetic Energy");
	plot_->axisLeft()->setAxisNameFont(QFont("Helvetica", 6));
    plot_->axisLeft()->setTickLabelFont(QFont("Helvetica", 6));
    plot_->axisLeft()->setAxisName("Photon Energy");
    plot_->axisLeft()->showGrid(false);

    // Zoooming tools
    plot_->addTool(new MPlotDragZoomerTool);
    plot_->addTool(new MPlotWheelZoomerTool);

	// Set the margins for the plot. Test values
    plot_->setMarginLeft(10);
	plot_->setMarginBottom(15);
    plot_->setMarginRight(10);
	plot_->setMarginTop(2);

	// Enable some convenient zoom tools.
	plotView_->setPlot(plot_);
    plotView_->setMinimumHeight(650);
    plotView_->setMinimumWidth(800);

	scanListWidget_ = new QListWidget(this);
    addScansButton_ = new QPushButton("Add Scans", this);
    clearScansButton_ = new QPushButton("Clear Map", this);
	createMapButton_ = new QPushButton("Create Map", this);
    createMapButton_->setIcon(QIcon("/home/david/code/XPSDisplay/XPSDisplay/start4.png"));
    createMapButton_->setIconSize(QSize(25,25));

	mainLayout_ = new QHBoxLayout;
	buttonsLayout_ = new QHBoxLayout;
	panelLayout_ = new QVBoxLayout;
	mapLayout_ = new QVBoxLayout;

	mapLayout_->addWidget(plotView_);

    buttonsLayout_->addWidget(addScansButton_);
    buttonsLayout_->addWidget(clearScansButton_);

	panelLayout_->addWidget(scanListWidget_);
	panelLayout_->addLayout(buttonsLayout_);
	panelLayout_->addWidget(createMapButton_);

	mainLayout_->addLayout(panelLayout_);
	mainLayout_->addLayout(mapLayout_);

	setLayout(mainLayout_);

    connect(addScansButton_, SIGNAL(clicked()), this, SLOT(openFileDialogBatch()));
    connect(this, SIGNAL(batchScansAdded()), this, SLOT(updateListFromBatch()));
    connect(createMapButton_, SIGNAL(clicked()), this, SLOT(displayMap()));
    connect(clearScansButton_, SIGNAL(clicked()), this, SLOT(clearListAndMap()));

}

void XPSDisplayWidget::openFileDialogBatch()
{

    if(!batchAddScanDialog_){

        batchAddScanDialog_ = new QDialog(this);
        batchAddScanDialog_->setFixedSize(600, 320);

        findScanButton_ = new QPushButton("Find Scans");
        addSelectedScansButton_ = new QPushButton("Add Scans");

        listOfScans_ = new QListWidget;

        QHBoxLayout *mainLayout = new QHBoxLayout;
        QVBoxLayout *buttonLayout = new QVBoxLayout;

        buttonLayout->addWidget(findScanButton_);
        buttonLayout->addWidget(addSelectedScansButton_);

        mainLayout->addWidget(listOfScans_);
        mainLayout->addLayout(buttonLayout);

        batchAddScanDialog_->setLayout(mainLayout);

        connect(findScanButton_, SIGNAL(clicked()), this, SLOT(findBatchFiles()));
        connect(addSelectedScansButton_, SIGNAL(clicked()), this, SLOT(addBatchScans()));

    }

    batchAddScanDialog_->exec();


}

void XPSDisplayWidget::findBatchFiles()
{
	QFileDialog dialog(this);
	dialog.setDirectory("/home/david/Desktop/Au");
	dialog.setFileMode(QFileDialog::ExistingFiles);
	dialog.setNameFilter(tr("Text (*.txt)"));
	if(dialog.exec()){

        fileNames = QStringList(dialog.selectedFiles());
        listOfScans_->addItems(fileNames);
        numberOfScans_ = fileNames.count();

		dialog.close();
    }
}


void XPSDisplayWidget::addBatchScans()
{
    model_->loadScanFromFiles(fileNames);
    batchAddScanDialog_->close();
	emit batchScansAdded();
}



//Ask XPSMapViewModel to call loadScanIntoMap()
//Function creates new XPSMap(scans_) then calls XPSMap::buildXPSMap
//This fills in a MPlotSimpleImageData class which is given to
//data2D_ via the model
void XPSDisplayWidget::displayMap()
{
    model_->loadScanIntoMap();

    //Create parameters to construct a MPlotSimleImageData object
    int size = model_->map()->scans().count();
    int scansPerFile = model_->map()->scans().at(0)->numOfPoints();

    if(!data2D_){

        data2D_ = new MPlotSimpleImageData(size, scansPerFile);
        data2D_ = model_->map()->data();

        plot2D_ = new MPlotImageBasic(data2D_);
        plot2D_->setColorMap(MPlotColorMap::Jet);

        plot_->addItem(plot2D_);
        plot_->axisLeft()->showGrid(false);
        plot_->colorLegend()->show();

    }

    plotView_->setPlot(plot_);

}

void XPSDisplayWidget::updateListFromBatch()
{
    for(int i = 0; i < numberOfScans_; i++){
		scanListWidget_->addItem(model_->scanName(i));
	}
}

void XPSDisplayWidget::clearListAndMap()
{
    scanListWidget_->clear();
    //ToDo: clear plot
}


XPSDisplayWidget::~XPSDisplayWidget()
{
	if (batchAddScanDialog_){
		batchAddScanDialog_->deleteLater();
		batchAddScanDialog_ = 0;
	}
}

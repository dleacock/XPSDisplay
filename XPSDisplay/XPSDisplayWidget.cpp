#include "XPSDisplayWidget.h"
#include <QPixmap>
#include <QFileDialog>

XPSDisplayWidget::XPSDisplayWidget(QWidget *parent) :
	QWidget(parent)
{
	model_ = new XPSMapViewModel();

	numberOfScans_ = 0;

	addScanDialog_ = 0;
	optionDialog_ = 0;
    batchAddScanDialog_ = 0;
    data2D_ = 0;
    plot2D_ = 0;

	normalized = false;

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

	connect(addScanButton_, SIGNAL(clicked()), this, SLOT(alertDialog()));
	connect(this, SIGNAL(scanAdded()), this, SLOT(updateList()));
	connect(this, SIGNAL(batchScansAdded()), this, SLOT(updateListFromBatch()));
	connect(removeScanButton_, SIGNAL(clicked()), this, SLOT(removeScan()));
	connect(createMapButton_, SIGNAL(clicked()), this, SLOT(displayMap()));



}

void XPSDisplayWidget::alertDialog()
{
    if(!optionDialog_){
        optionDialog_ = new QDialog(this);
        optionDialog_->setFixedSize(320, 140);

        // Experimenting with different fonts and sizes. For final build I'd like to use a stylesheet
        normalButton_ = new QPushButton("Single File");
        normalButton_->setFont(QFont("Helvetica", 12));
        batchButton_ = new QPushButton("Add Multiple Files");
        batchButton_->setFont(QFont("Monospace", 12));
        infoText_ = new QLabel("Select multiple files to add without normalization or individual files with normalization.");
        infoText_->setWordWrap(true);

        QVBoxLayout *mainLayout = new QVBoxLayout;
        QHBoxLayout *subLayout = new QHBoxLayout;

        subLayout->addWidget(normalButton_);
        subLayout->addWidget(batchButton_);

        mainLayout->addWidget(infoText_);
        mainLayout->addLayout(subLayout);

        optionDialog_->setLayout(mainLayout);

        connect(normalButton_, SIGNAL(clicked()), this, SLOT(openFileDialogNormalize()));
        connect(batchButton_, SIGNAL(clicked()), this, SLOT(openFileDialogBatch()));

    }
	optionDialog_->exec();
}

void XPSDisplayWidget::openFileDialogBatch()
{
    optionDialog_->close();

    normalized = false;

    if(!batchAddScanDialog_){

        batchAddScanDialog_ = new QDialog(this);
        batchAddScanDialog_->setFixedSize(600, 320);

        photonEnergyStartLabel_ = new QLabel("hv initial: ");
        photonEnergyStartLabel_->setFixedWidth(70);
        photonEnergyStart_ = new QLineEdit("0");
        photonEnergyStart_->setFixedWidth(75);

        hvLabel_ = new QLabel("step size: ");
        hvLabel_->setFixedWidth(70);
        photonEnergyStep_ = new QLineEdit("0");
        photonEnergyStep_->setFixedWidth(75);

        paramStatusHV_ = new QLabel();
        paramStatusHV_->setPixmap(QIcon("/home/david/code/XPSDisplay/XPSDisplay/cross-mark1.png").pixmap(20));

        findScanButton_ = new QPushButton("Find Scans");
        addFileName_ = new QLineEdit("File Selected");
        addScansButton_ = new QPushButton("Add Scans");

        listOfScans_ = new QListWidget;

        QHBoxLayout *mainLayout = new QHBoxLayout;
        QHBoxLayout *hvLayout = new QHBoxLayout;
        QVBoxLayout *panelLayout = new QVBoxLayout;

        hvLayout->addWidget(photonEnergyStartLabel_);
        hvLayout->addWidget(photonEnergyStart_);
        hvLayout->addWidget(hvLabel_);
        hvLayout->addWidget(photonEnergyStep_);
        hvLayout->addWidget(paramStatusHV_);

        panelLayout->addLayout(hvLayout);
        panelLayout->addWidget(findScanButton_);
        panelLayout->addWidget(addScansButton_);

        mainLayout->addWidget(listOfScans_);
        mainLayout->addLayout(panelLayout);

        batchAddScanDialog_->setLayout(mainLayout);

        connect(findScanButton_, SIGNAL(clicked()), this, SLOT(findBatchFiles()));
        connect(photonEnergyStep_, SIGNAL(editingFinished()), this, SLOT(checkParam()));
        connect(addScansButton_, SIGNAL(clicked()), this, SLOT(addBatchScans()));

    }

    batchAddScanDialog_->exec();


}
//ToDo: User needs to remain in this dialog until all the files they want have been added.
void XPSDisplayWidget::openFileDialogNormalize(){

    optionDialog_->close();

    normalized = true;

    // Add new scan dialog
    addScanDialog_ = new QDialog(this);
    addScanDialog_->setFixedSize(380, 120);

    if(addScanDialog_){

        // Should I move this to the constructor? Is it ok that
        // these widgets get created, and I assume destroyed, when the
        // window opens and closes?
        i0Label_ = new QLabel("I0: ");
        i0Label_->setFixedWidth(20);
        addI0_ = new QLineEdit("0");
        addI0_->setFixedWidth(75);
        paramStatusI0_ = new QLabel();
        paramStatusI0_->setPixmap(QIcon("/home/david/code/XPSDisplay/XPSDisplay/cross-mark1.png").pixmap(20));

        hvLabel_ = new QLabel("hv: ");
        hvLabel_->setFixedWidth(20);
        addPhotonEnergy_ = new QLineEdit("0");
        addPhotonEnergy_->setFixedWidth(75);
        paramStatusHV_ = new QLabel();
        paramStatusHV_->setPixmap(QIcon("/home/david/code/XPSDisplay/XPSDisplay/cross-mark1.png").pixmap(20));

        findScanButton_ = new QPushButton("Find Scan");
        addFileName_ = new QLineEdit("File Selected");
        addScan_ = new QPushButton("Add this scan");

        QVBoxLayout *mainLayout = new QVBoxLayout;
        QHBoxLayout *subLayout = new QHBoxLayout;
        QVBoxLayout *paramLayout = new QVBoxLayout;

        QHBoxLayout *i0Layout = new QHBoxLayout;
        i0Layout->addWidget(i0Label_);
        i0Layout->addWidget(addI0_);
        i0Layout->addWidget(paramStatusI0_);
        i0Layout->setAlignment(Qt::AlignLeft);

        QHBoxLayout *hvLayout = new QHBoxLayout;
        hvLayout->addWidget(hvLabel_);
        hvLayout->addWidget(addPhotonEnergy_);
        hvLayout->addWidget(paramStatusHV_);
        hvLayout->setAlignment(Qt::AlignLeft);

        QHBoxLayout *fileLayout = new QHBoxLayout;
        fileLayout->addWidget(addFileName_);
        fileLayout->addWidget(findScanButton_);

        paramLayout->addLayout(i0Layout);
        paramLayout->addLayout(hvLayout);

        subLayout->addLayout(paramLayout);
        subLayout->addWidget(addScan_);

        mainLayout->addLayout(fileLayout);
        mainLayout->addLayout(subLayout);

        addScanDialog_->setLayout(mainLayout);

        connect(findScanButton_, SIGNAL(clicked()), this, SLOT(findFile()));
        connect(addScan_, SIGNAL(clicked()), this, SLOT(addScan()));
        connect(addI0_, SIGNAL(editingFinished()), this, SLOT(checkParam()));
        connect(addPhotonEnergy_, SIGNAL(editingFinished()), this, SLOT(checkParam()));
    }

    addScanDialog_->exec();
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

// ToDo: this function needs to take into account an incrimentally increase hv values
void XPSDisplayWidget::addBatchScans()
{
    qreal hvStep = photonEnergyStep_->text().toDouble();
    qreal hvStart = photonEnergyStart_->text().toDouble();
    model_->loadScanFromFiles(hvStart, hvStep, fileNames);
	batchAddScanDialog_->close();
	emit batchScansAdded();
}


// Opens a new QFileDialog
void XPSDisplayWidget::findFile(){

	// Go right to my personal Au scan directory. ToDo: Set to /home/ on release
	fileName_ = QFileDialog::getOpenFileName(this, tr("Add New Scan"),"/home/david/Desktop/Au", tr("Text (*.txt)"));
	addFileName_->setText(fileName_);

}

void XPSDisplayWidget::addScan()
{
    qreal hv = addPhotonEnergy_->text().toDouble();
    qreal i0 = addI0_->text().toDouble();

    model_->loadScansFromFilesNormalize(i0, hv, fileName_);

	//update the list of files
	numberOfScans_++;
	emit scanAdded();
	addScanDialog_->close();
}

void XPSDisplayWidget::removeScan()
{
	//Remove scan from list widget
	scanListWidget_->takeItem(numberOfScans_-1);

	//Remove scan from QList<XPS>
	model_->removeScan();

	numberOfScans_--;

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
	qDebug() << numberOfScans_;
	for(int i = 0; i < numberOfScans_; i++){
		scanListWidget_->addItem(model_->scanName(i));
	}
}

void XPSDisplayWidget::updateList()
{
	// Using a global variable to track number of scans for sole
	// purpose of knowing the index value of the top scan.
	// I could create a getter in the model to know the number of scans too
	scanListWidget_->addItem(model_->scanName(numberOfScans_-1));

}

// Dummy icons for now
// ToDo: Remove ability to add scan until both params are approved
void XPSDisplayWidget::checkParam()
{
	if(normalized){

		if(addPhotonEnergy_->text().toDouble() > 0)
			paramStatusHV_->setPixmap(QIcon("/home/david/code/XPSDisplay/XPSDisplay/checkmark21.png").pixmap(20));
		else
			paramStatusHV_->setPixmap(QIcon("/home/david/code/XPSDisplay/XPSDisplay/cross-mark1.png").pixmap(20));

		if(addI0_->text().toDouble())
			paramStatusI0_->setPixmap(QIcon("/home/david/code/XPSDisplay/XPSDisplay/checkmark21.png").pixmap(20));
		else
			paramStatusI0_->setPixmap(QIcon("/home/david/code/XPSDisplay/XPSDisplay/cross-mark1.png").pixmap(20));
	}
	else{

		if(photonEnergyStep_->text().toDouble() > 0)
			paramStatusHV_->setPixmap(QIcon("/home/david/code/XPSDisplay/XPSDisplay/checkmark21.png").pixmap(20));
		else
			paramStatusHV_->setPixmap(QIcon("/home/david/code/XPSDisplay/XPSDisplay/cross-mark1.png").pixmap(20));

	}
}

XPSDisplayWidget::~XPSDisplayWidget()
{
	if (addScanDialog_){
		addScanDialog_->deleteLater();
		addScanDialog_ = 0;
	}
	if (optionDialog_){
		optionDialog_->deleteLater();
		optionDialog_ = 0;
	}
	if (batchAddScanDialog_){
		batchAddScanDialog_->deleteLater();
		batchAddScanDialog_ = 0;
	}
}

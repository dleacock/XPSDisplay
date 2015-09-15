#include "XPSDisplayWidget.h"
#include <QPixmap>

XPSDisplayWidget::XPSDisplayWidget(QWidget *parent) :
	QWidget(parent)
{
	// This is for testing purposes. Adding an image to show location of 2DMap
	QPixmap testMapImage("/home/david/code/XPSDisplay/XPSDisplay/image.jpg");
	QPixmap testMapImageScaled = testMapImage.scaled(QSize(400, 400), Qt::KeepAspectRatio);

	// This will be removed and replaced by Mplot widget
	imageLabel_ = new QLabel(this);
	imageLabel_->setPixmap(testMapImageScaled);

	scanListWidget_ = new QListWidget(this);
	addScanButton_ = new QPushButton("Add Scan", this);
	removeScanButton_ = new QPushButton("Remove Scan", this);
	createMapButton_ = new QPushButton("Create Map", this);

	mainLayout_ = new QHBoxLayout;
	buttonsLayout_ = new QHBoxLayout;
	panelLayout_ = new QVBoxLayout;
	mapLayout_ = new QVBoxLayout;

	// Replace with MPlot widget
	mapLayout_->addWidget(imageLabel_);

	buttonsLayout_->addWidget(addScanButton_);
	buttonsLayout_->addWidget(removeScanButton_);

	panelLayout_->addWidget(scanListWidget_);
	panelLayout_->addLayout(buttonsLayout_);
	panelLayout_->addWidget(createMapButton_);

	mainLayout_->addLayout(panelLayout_);
	mainLayout_->addLayout(mapLayout_);

	setLayout(mainLayout_);

}



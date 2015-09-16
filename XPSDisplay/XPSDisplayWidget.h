#ifndef XPSDISPLAYWIDGET_H
#define XPSDISPLAYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QListWidget>

#include "MPlot/MPlotWidget.h"
#include "MPlot/MPlot.h"
#include "MPlot/MPlotImageData.h"
#include "MPlot/MPlotImage.h"



class XPSDisplayWidget : public QWidget
{
	Q_OBJECT
public:
	XPSDisplayWidget(QWidget *parent = 0);
signals:

public slots:

protected:
	QHBoxLayout *mainLayout_;
	QHBoxLayout *buttonsLayout_;
	QVBoxLayout *panelLayout_;
	QVBoxLayout *mapLayout_;

	// List of current 1D XPS Scans to be added to map
	QListWidget *scanListWidget_;
	// Add new XPS Scan
	QPushButton *addScanButton_;
	// Remove recently added scan
	QPushButton *removeScanButton_;
	// Create map based off XPS scans in list widget
	QPushButton *createMapButton_;


	// Testing purposes, dummy image for map
	QLabel *imageLabel_;

    // MPlot widget that holds plot
    MPlotWidget *plotView_;
    // The actual plot itself
    MPlot *plot_;
    // 2D Data for image
    MPlotSimpleImageData *data2D_;
    // Image to be given to plot
    MPlotImageBasic *plot2D_;




};

#endif // XPSDISPLAYWIDGET_H

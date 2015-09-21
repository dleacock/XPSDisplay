#ifndef XPSDISPLAYWIDGET_H
#define XPSDISPLAYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QListWidget>
#include <QDialog>
#include <QLineEdit>

#include "MPlot/MPlotWidget.h"
#include "MPlot/MPlot.h"
#include "MPlot/MPlotImageData.h"
#include "MPlot/MPlotImage.h"

#include "XPSMapViewModel.h"


class XPSDisplayWidget : public QWidget
{
	Q_OBJECT
public:
	XPSDisplayWidget(QWidget *parent = 0);
signals:
	void scanAdded();
public slots:
    void openFileDialog();
    void findFile();
    void addScan();
    void removeScan();
    void displayMap();
    void updateList();

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

	// ToDo: Add new scan dialog window
	// needs to include fields to input I0 and hv
	QDialog *addScanDialog_;
	// Photon energy
	QLineEdit *addPhotonEnergy_;
	// Incident photon amount
	QLineEdit *addI0_;
	// Find scan button to open QFileDialog
	QPushButton *findScanButton_;
	// The current selected file to be addeds path
	QLineEdit *addFileName_;
	// Add current scan
	QPushButton *addScan_;
	// Labels fir i0 and hv
	QLabel *i0Label_;
	QLabel *hvLabel_;


	QString fileName_;

	XPSMapViewModel *model_;

	int numberOfScans_;



};

#endif // XPSDISPLAYWIDGET_H

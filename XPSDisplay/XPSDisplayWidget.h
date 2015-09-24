#ifndef XPSDISPLAYWIDGET_H
#define XPSDISPLAYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QListWidget>
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>

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
	~XPSDisplayWidget();

signals:
	void scanAdded();
	void batchScansAdded();
public slots:
	void openFileDialogNormalize();
	void openFileDialogBatch();
	void findFile();
	void findBatchFiles();
	void addScan();
	void addBatchScans();
	void removeScan();
	void displayMap();
	void updateList();
	void updateListFromBatch();
	void checkParam();
	void alertDialog();

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

	// Let user select which option they want. There might be a better way to prompt them that doesn't require a new dialog
	QDialog *optionDialog_;
	// Select normalized
	QPushButton *normalButton_;
	// Select not normalized and do a batch add
	QPushButton *batchButton_;
	// A description of the options
	QLabel *infoText_;

	// needs to include fields to input I0 and hv
	QDialog *addScanDialog_;
	// batch add dialog
	QDialog *batchAddScanDialog_;
	// Photon energy
	QLineEdit *addPhotonEnergy_;
	// Incident photon amount
	QLineEdit *addI0_;
	// Find scan button to open QFileDialog
	QPushButton *findScanButton_;
	// Add all scans
	QPushButton *addScansButton_;
	// The current selected file to be addeds path
	QLineEdit *addFileName_;
	// Add current scan
	QPushButton *addScan_;
	// Labels for i0 and hv
	QLabel *i0Label_;
	QLabel *hvLabel_;

	// Icon to show if params are acceptable
	QLabel *paramStatusI0_;
	QLabel *paramStatusHV_;

	//Widgets for non-normalized batch add scans dialog
	QListWidget *listOfScans_;

	QStringList *fileNames_;

	// Enter photon energy step size
	QLineEdit *photonEnergyStep_;
	// Initial photon energy
	QLineEdit *photonEnergyStart_;
	QLabel *photonEnergyStartLabel_;



	QString fileName_;

	XPSMapViewModel *model_;

	int numberOfScans_;

	bool normalized;


};

#endif // XPSDISPLAYWIDGET_H

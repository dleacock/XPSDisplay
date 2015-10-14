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

	void openFileDialogBatch();
	void findBatchFiles();
    void addBatchScans();
    void displayMap();
    void updateListFromBatch();
    void clearListAndMap();


protected:
	QHBoxLayout *mainLayout_;
	QHBoxLayout *buttonsLayout_;
	QVBoxLayout *panelLayout_;
	QVBoxLayout *mapLayout_;

	// List of current 1D XPS Scans to be added to map
	QListWidget *scanListWidget_;
    // Add new XPS Scans
    QPushButton *addScansButton_;
    // Clear list of scans and map
    QPushButton *clearScansButton_;
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

    // batch add dialog
	QDialog *batchAddScanDialog_;
    // Find scan button to open QFileDialog
	QPushButton *findScanButton_;
	// Add all scans
    QPushButton *addSelectedScansButton_;
	// The current selected file to be addeds path
	QLineEdit *addFileName_;
	// Add current scan
	QPushButton *addScan_;


	//Widgets for non-normalized batch add scans dialog
	QListWidget *listOfScans_;
    // List of all the igor files added
    QStringList fileNames;


	XPSMapViewModel *model_;

	int numberOfScans_;


};

#endif // XPSDISPLAYWIDGET_H

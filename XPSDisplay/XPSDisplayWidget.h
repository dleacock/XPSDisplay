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
#include <QSlider>

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

    void updateBrightness(int newValue);
    void updateContrast(int newValue);
    void updateGamma(int newValue);


protected:
	QHBoxLayout *mainLayout_;
	QHBoxLayout *buttonsLayout_;
	QVBoxLayout *panelLayout_;
	QVBoxLayout *mapLayout_;
    QHBoxLayout *controlsLayout_;
    QVBoxLayout *controlsHolder_;
    QHBoxLayout *contrastLayout_;
    QHBoxLayout *brightnessLayout_;
    QHBoxLayout *gammaLayout_;


	// List of current 1D XPS Scans to be added to map
	QListWidget *scanListWidget_;
    // Add new XPS Scans
    QPushButton *addScansButton_;
    // Clear list of scans and map
    QPushButton *clearScansButton_;
	// Create map based off XPS scans in list widget
	QPushButton *createMapButton_;

    // Color controls for plot2D map
    // Default values from MPlotColorMap are brightness = 0., contrast and gamma = 1.
    QLabel *contrastLabel_;
    QLabel *brightnessLabel_;
    QLabel *gammaLabel_;
    QSlider *contrastSlider_;
    QSlider *brightnessSlider_;
    QSlider *gammaSlider_;

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

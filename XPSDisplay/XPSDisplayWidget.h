#ifndef XPSDISPLAYWIDGET_H
#define XPSDISPLAYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QListWidget>


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

};

#endif // XPSDISPLAYWIDGET_H

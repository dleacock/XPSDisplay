#include "XPSDisplayWidget.h"
#include <QPixmap>

XPSDisplayWidget::XPSDisplayWidget(QWidget *parent) :
	QWidget(parent)
{
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

}



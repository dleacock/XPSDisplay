#-------------------------------------------------
#
# Project created by QtCreator 2015-09-11T11:44:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#LIBS += -L/home/david/code/XPSDisplay/XPSDisplay/MPlot -lMPlot
INCLUDEPATH += /home/david/code/XPSDisplay/XPSDisplay
message($$INCLUDEPATH)


TARGET = XPSDisplay
TEMPLATE = app

SOURCES += main.cpp\
    XPSMap.cpp \
    XPSScan.cpp \
    XPSDisplayWidget.cpp \
    /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlot.cpp \
    /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotAbstractTool.cpp \
    /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotAxis.cpp \
    /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotColorMap.cpp \
    /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotImage.cpp \
     /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotImageData.cpp \
 /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotItem.cpp \
 /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotLegend.cpp \
 /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotMarker.cpp \
 /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotPoint.cpp \
 /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotSeries.cpp \
 /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotSeriesData.cpp \
 /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotTools.cpp \
 /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotWidget.cpp \
 /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotAxisScale.cpp \
 /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotRectangle.cpp \
 /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotMarkerTransparentVerticalRectangle.cpp \
 /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotColorLegend.cpp \
 /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotImageRangeDialog.cpp \
    XPSMapViewModel.cpp

HEADERS  += main.h \
    XPSMap.h \
    XPSScan.h \
    XPSDisplayWidget.h \
    /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlot.h \
    /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotAbstractTool.h \
    /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotAxis.h \
    /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotColorMap.h \
    /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotImage.h \
     /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotImageData.h \
 /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotItem.h \
 /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotLegend.h \
 /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotMarker.h \
 /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotPoint.h \
 /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotSeries.h \
 /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotSeriesData.h \
 /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotTools.h \
 /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotWidget.h \
 /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotAxisScale.h \
 /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotRectangle.h \
 /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotMarkerTransparentVerticalRectangle.h \
 /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotColorLegend.h \
 /home/david/code/XPSDisplay/XPSDisplay/MPlot/MPlotImageRangeDialog.h \
    XPSMapViewModel.h


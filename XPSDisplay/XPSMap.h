#ifndef XPSMAP_H
#define XPSMAP_H

#include "XPSScan.h"
#include "MPlot/MPlotImageData.h"

// At first pass at writing this class I'm going to have it take in
// a vector of scans, and have the buildXPSMap unpack them and put them
// into a MPlotSimpleImageData variable that the class owns. Unsure if I should make
// XPS inherit from MPlotSimpleImage data or just have it as a member variable
// or have buildXPSMap return one.

class XPSMap
{

public:
	XPSMap(QList<XPSScan> scans);

	void buildXPSMap();
	QList<XPSScan> *scans() const { return scans_; }
	MPlotSimpleImageData *data() const { return data2D_; }

private:
	QList<XPSScan> *scans_;
	MPlotSimpleImageData *data2D_;

	// Each scan consists of a series of scans, this number is that total.
	int dataSize_;

};

#endif // XPSMAP_H

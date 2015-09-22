#include "XPSMapViewModel.h"


XPSMapViewModel::XPSMapViewModel()
{


}

// This will be provided a list (QString file names?) and iterater
// through each value on the list, create an XPS scan for each one
// then store it in the QList<XPSScan *>
void XPSMapViewModel::loadScansFromFilesNormalize(qreal i0, qreal hv, QString fileName)
{
	XPSScan *scan = new XPSScan(i0, hv, fileName);
    scans_.append(scan);
}


void XPSMapViewModel::loadScanIntoMap()
{
	map_ = new XPSMap(scans_);
    map_->buildXPSMap();
}

QString XPSMapViewModel::scanName(int index)
{
	return scans_.at(index)->filePath();
}

void XPSMapViewModel::removeScan()
{
    scans_.removeLast();
}

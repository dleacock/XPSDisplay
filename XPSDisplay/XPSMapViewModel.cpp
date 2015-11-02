#include "XPSMapViewModel.h"


XPSMapViewModel::XPSMapViewModel()
{
    map_ = 0;

}

// This will be provided a list (QString file names?) and iterater
// through each value on the list, create an XPS scan for each one
// then store it in the QList<XPSScan *>
void XPSMapViewModel::loadScansFromFilesNormalize(qreal i0, qreal hv, QString fileName)
{
	XPSScan *scan = new XPSScan(i0, hv, fileName);
	scans_.append(scan);
}

void XPSMapViewModel::loadScanFromFiles(qreal hvStart,qreal hvStepSize, QStringList files)
{
    qreal hv = hvStart;

    for(int i = 0; i < files.count(); i++){
		XPSScan *scan = new XPSScan(hv, files.at(i));
		scans_.append(scan);
        hv += hvStepSize;
	}

}

void XPSMapViewModel::loadScanFromFiles(QStringList files)
{
    for(int i = 0; i < files.count(); i++){
        XPSScan *scan = new XPSScan(files.at(i));
        scans_.append(scan);

    }

}

void XPSMapViewModel::loadScanIntoMap()
{
    if(!map_){
        map_ = new XPSMap(scans_);
        map_->buildXPSMap();
    }

}

QString XPSMapViewModel::scanName(int index)
{
	return scans_.at(index)->filePath();
}

void XPSMapViewModel::removeScan()
{
	scans_.removeLast();
}

void XPSMapViewModel::removeAllScans()
{
    for(int i = 0; i < scans_.size(); i++){
        delete scans_.at(i);
        }
    scans_.clear();
    map_ = 0;
}

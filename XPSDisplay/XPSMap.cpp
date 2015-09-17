#include "XPSMap.h"

XPSMap::XPSMap(QList<XPSScan> scans)
{

    scans_ = scans;

    for(int i = 0; i < scans.count(); i++)
        dataSize_ += scans[i].numOfPoints();

    data2D_ = new MPlotSimpleImageData(dataSize_, dataSize_);

}

// read through all XPSScans, store data in MPlotSimpleImageData's vectors
// 1. Create temp vectors
// 2. Loop through scans,  continuely appending temp vectors
// 3. pass temp vectors into MPlotSimpleImageData::setXValues setYValues
void XPSMap::buildXPSMap()
{
    QVector<qreal> tempKineticValues = QVector<qreal>(dataSize_);
    QVector<qreal> tempCountsValues = QVector<qreal>(dataSize_);

    //This value will run from 0 to dataSize_
    int tempIndex = 0;
    for(int i = 0; i < scans_->count(); i++){
	for(int j = 0; j < scans_[i]->numOfPoints; j++){

		// ToDo: Need to add a getter for XPSScan kinetic/counts
		// pass those getter'd values into temp vectors
		tempKineticValues[tempIndex] = scans_[i]->kineticEnergy(j);
		tempCountsValues[tempIndex] = scans_[i]->detectionCount(j);

		tempIndex++;

        }
    }

    // ToDo: Double check notes as to what axes values need to be
    data2D_->setXValues(0,dataSize_-1, tempKineticValues.data());
    data2D_->setYValues(0,dataSize_-1, tempCountsValues.data());


}

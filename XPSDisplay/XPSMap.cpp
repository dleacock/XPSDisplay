#include "XPSMap.h"

XPSMap::XPSMap(QList<XPSScan*> scans)
{
    dataSize_ = 0;
    scans_ = scans;

    for(int i = 0; i < scans_.count(); i++)
        dataSize_ += scans_.at(i)->numOfPoints();
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
    QVector<qreal> tempPhotonValues = QVector<qreal>(dataSize_);

    //This value will run from 0 to dataSize_
    int tempIndex = 0;
    for(int i = 0; i < scans_.count(); i++){
    for(int j = 0; j < scans_.at(i)->numOfPoints(); j++){

        // kinetic and counts are index based as each measurement is different
        // however photon energy changes per full scan
        tempKineticValues[tempIndex] = scans_.at(i)->kineticEnergy(j);
        tempCountsValues[tempIndex] = scans_.at(i)->detectionCount(j);
        tempPhotonValues[tempIndex] = scans_.at(i)->photonEnergy();

        // Setting the Z while in the loop instead of laying down as a vector when I'm done
        // since I'm not sure at what index each scan starts and stops at.
        data2D_->setZ(tempIndex, tempIndex, tempCountsValues[tempIndex]);

        tempIndex++;

        }

    }

    // X-axis: Kinetic Energy
    // Y-axis: Photon Energy
    // Z-aixs: Counts
    data2D_->setXValues(0, dataSize_-1, tempKineticValues.data());
    data2D_->setYValues(0, dataSize_-1, tempPhotonValues.data());


}

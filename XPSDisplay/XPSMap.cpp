#include "XPSMap.h"

XPSMap::XPSMap(QList<XPSScan*> scans)
{
    dataSize_ = 0;
    data2D_= 0;
    scans_ = scans;

    pointsPerFile_ = scans_.at(0)->numOfPoints();
    dataSize_ = pointsPerFile_ * scans_.count();

    // Let the x-axis be KE, which is the dep. axis in the igor files. Ki to Kf is the same
    // for each file, called pointsPerFile_.
    // Y-axis will be photon energy, which increases with each scan file. The dimension of this will be the total number of scan files
    if(!data2D_){
        data2D_ = new MPlotSimpleImageData(pointsPerFile_, scans_.count());
     }
}

// read through all XPSScans, store data in MPlotSimpleImageData's vectors
// 1. Create temp vectors
// 2. Loop through scans,  continuely appending temp vectors
// 3. pass temp vectors into MPlotSimpleImageData::setXValues setYValues
void XPSMap::buildXPSMap()
{
    //The total number of kinetic energy values remains the same in every file, in this case its 660
    QVector<qreal> tempKineticValues = QVector<qreal>(pointsPerFile_);
    //The counts value will be the z in the 2d map. For every K value in every file there is a count value
    QVector<qreal> tempCountsValues = QVector<qreal>(dataSize_);
    //Photon values start at some initial hv and increase by some defined value. Each scan file has its own hv value
    QVector<qreal> tempPhotonValues = QVector<qreal>(scans_.count());

    //Since every file has the same range of Ki to Kf we will just use the first file to fill our vector
    for(int i = 0; i < pointsPerFile_; i++){
        tempKineticValues[i] = scans_.at(0)->kineticEnergy(i);
        qDebug() << "KE " << i << ": " << tempKineticValues[i];
    }
    // Grab each hv value from every single file
    for(int i = 0; i < scans_.count(); i++){
        tempPhotonValues[i] = scans_.at(i)->photonEnergy();
        qDebug() << "HV " << i << ": " << tempPhotonValues[i];
    }

    int keSize = pointsPerFile_;
    int hvSize = scans_.count();

    for (int i = 0; i < hvSize; i++){
        double i0 = scans_.at(i)->incomingPhotons();
        for (int j = 0; j < keSize; j++){

            tempCountsValues[i+j*hvSize] = scans_.at(i)->detectionCount(j)/i0;
        }
    }

    //Set all values down at once after vectors are filled.
    data2D_->setXValues(0, pointsPerFile_ - 1, tempKineticValues.data());
    data2D_->setYValues(0, scans_.count() - 1, tempPhotonValues.data());
    data2D_->setZValues(0, 0, pointsPerFile_ - 1, scans_.count() - 1, tempCountsValues.data());

}




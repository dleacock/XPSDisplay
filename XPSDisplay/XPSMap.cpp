#include "XPSMap.h"

XPSMap::XPSMap(QList<XPSScan*> scans)
{
    dataSize_ = 0;
    data2D_= 0;
    scans_ = scans;

    //This determines the total count of all points from all scan files.
    //Is used to determine the max length of temp vectors used for storing
    //data from the scans.
    for(int i = 0; i < scans_.count(); i++){
        for(int j = 0; j < scans_.at(i)->numOfPoints(); j++){
               dataSize_ += scans_.at(i)->numOfPoints();
        }
    }

    // I believe each scan file has the same number of scans.
    // That was the case for this particular experiment where each scan file has 660 points collected
    // However this may not be the general case.
    pointsPerFile_ = scans_.at(0)->numOfPoints();

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
    }
    // Grab each hv value from every single file
    for(int i = 0; i < scans_.count(); i++){
        tempPhotonValues[i] = scans_.at(i)->photonEnergy();
    }
    // Run through each scan file and grab all detection counts and store continously in vector
    int countIndex = 0;
    for(int i = 0; i < scans_.count(); i++){
        for(int j = 0; j < scans_.at(i)->numOfPoints(); j++){
            tempCountsValues[countIndex] = scans_.at(i)->detectionCount(j);
            countIndex++;
        }
    }
    //Set all values down at once after vectors are filled.
    data2D_->setXValues(0, pointsPerFile_ - 1, tempKineticValues.data());
    data2D_->setYValues(0, scans_.count() - 1, tempPhotonValues.data());
    data2D_->setZValues(0, pointsPerFile_ - 1, 0, scans_.count() - 1, tempCountsValues.data());

}




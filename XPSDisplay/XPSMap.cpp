#include "XPSMap.h"

XPSMap::XPSMap(QList<XPSScan*> scans)
{
    qDebug() << "After call 0";
    dataSize_ = 0;
    data2D_= 0;
    scans_ = scans;
     qDebug() << "After call 1";
    for(int i = 0; i < scans_.count(); i++){
        qDebug() << "After call 2 ";
        qDebug() << "Scan #" << i+1;
        for(int j = 0; j < scans_.at(i)->numOfPoints(); j++)
        {
             qDebug() << "KE: " << scans_.at(i)->kineticEnergy(j);
        }
        qDebug() << "Number of points per scan file: " <<  scans_.at(i)->numOfPoints();
        dataSize_ += scans_.at(i)->numOfPoints();
    }
    // I believe each scan file has the same number of scans
    int scansPerFile = scans_.at(0)->numOfPoints();
    qDebug() << "dataSize_" << dataSize_;
    qDebug() << "After call 3";
     if(!data2D_){
        // CRASHING HERE!
        // SEGFAULT on qvector.h line 424
        // qMemSet(p->array, 0, asize * sizeof(T))
         // where T is real and asize = 500,000,000
        data2D_ = new MPlotSimpleImageData(scans_.count(), scansPerFile);
        qDebug() << "After call 4";
     }
      qDebug() << "After call 5";
}

// read through all XPSScans, store data in MPlotSimpleImageData's vectors
// 1. Create temp vectors
// 2. Loop through scans,  continuely appending temp vectors
// 3. pass temp vectors into MPlotSimpleImageData::setXValues setYValues
void XPSMap::buildXPSMap()
{
    qDebug() << "buildXPSMap 1";
    QVector<qreal> tempKineticValues = QVector<qreal>(dataSize_);
    QVector<qreal> tempCountsValues = QVector<qreal>(dataSize_);
    QVector<qreal> tempPhotonValues = QVector<qreal>(dataSize_);
    qDebug() << data2D_->count();
    qDebug() << "buildXPSMap 2";
    //This value will run from 0 to dataSize_
    int tempIndex = 0;
    for(int i = 0; i < scans_.count(); i++){
    for(int j = 0; j < scans_.at(i)->numOfPoints(); j++){
        qDebug() << "buildXPSMap 3";
        // kinetic and counts are index based as each measurement is different
        // however photon energy changes per full scan
        tempKineticValues[tempIndex] = scans_.at(i)->kineticEnergy(j);
        tempCountsValues[tempIndex] = scans_.at(i)->detectionCount(j);
        tempPhotonValues[tempIndex] = scans_.at(i)->photonEnergy();
        qDebug() << "VALUES: ";
        qDebug() << "KE @ " << i << scans_.at(i)->kineticEnergy(j);
        qDebug() << "C @ " << i << scans_.at(i)->detectionCount(j);
        qDebug() << "PE @ " << i << scans_.at(i)->photonEnergy();
        qDebug() << "buildXPSMap 4";
        // Setting the Z while in the loop instead of laying down as a vector when I'm done
        // since I'm not sure at what index each scan starts and stops at.
       // qreal test = tempCountsValues.at(tempIndex);
        qDebug() << "loop i,j: " << i << "," << j;
        //data2D_->setZ(tempKineticValues[tempIndex], tempPhotonValues[tempIndex], test);
        qDebug() << "buildXPSMap 5";
        tempIndex++;

        }

    }

    qDebug() << "buildXPSMap 6";
    // X-axis: Kinetic Energy
    // Y-axis: Photon Energy
    // Z-aixs: Counts
    data2D_->setXValues(0, dataSize_-1, tempKineticValues.data());
    data2D_->setYValues(0, dataSize_-1, tempPhotonValues.data());

    for(int i = 0; i < scans_.count(); i++){
        for(int j = 0; j <  scans_.count(); j++){
            data2D_->setZ(i, j,  1);
        }
    }


    //qDebug() << "buildXPSMap 7";

}

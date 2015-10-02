#ifndef XPSSCAN_H
#define XPSSCAN_H

#include <QVector>
#include <QTextStream>
#include <QDebug>
#include <QFile>
#include <QStringList>

/// This defines a single XPS Scan, the information that will populate this class will come from an IGOR text file

class XPSScan
{


public:
    // Constructor, overloaded to have option of noramlized data points
    XPSScan(qreal i0, qreal hv, QString filePath);
    // Not normalized, used in batch files selected
    XPSScan(qreal hv, QString filePath);
    // This will most likely be the final version where the hv and i0 values have been written into the igor file itself
    XPSScan(QString filePath);

    // Loads IGOR text file and populates member variables. It finds the beginning of the data and fills the kineticEnergy and detectionCounts list.
    // ToDo: This algorithm needs to be fixed. At the end of every IGOR file, after the data is done, there is a blank space. This function needs
    // to account for that.
    void loadFromFile(QString filePath);

    // Getters
    float incomingPhotons() const { return incomingPhotons_; }
    float photonEnergy() const { return photonEnergy_; }
    int numOfPoints() const { return numberOfPoints_; }
    QString filePath() const { return filePath_; }
    qreal kineticEnergy(int index) const { return kineticEnergy_.at(index); }
    qreal detectionCount(int index) const { return detectionCounts_.at(index); }


    // Setters
    void setI0(qreal I0);
    void setPhotonEnergy(qreal energy);


private:
    // Both i0 and photonEnergy (hv) are manually entered from GUI
    qreal incomingPhotons_;
    qreal photonEnergy_;

    // kineticEnergy and detectionCounts are populated by the IGOR text file
    QVector<qreal> kineticEnergy_;
    QVector<qreal> detectionCounts_;

    int numberOfPoints_;

    QString filePath_;



};

#endif // XPSSCAN_H

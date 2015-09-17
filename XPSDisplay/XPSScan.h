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
    // Constructor
    XPSScan();

    // Loads IGOR text file and populates member variables. It finds the beginning of the data and fills the kineticEnergy and detectionCounts list.
    void loadFromFile(QString filePath);

    // Getters
    float incomingPhotons() const { return incomingPhotons_; }
    float photonEnergy() const { return photonEnergy_; }
    int numOfPoints() const { return numberOfPoints_; }

    qreal kineticEnergy(int index) const { return kineticEnergy_[index]; }
    qreal detectionCount(int index) const { return detectionCounts_[index]; }


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



};

#endif // XPSSCAN_H

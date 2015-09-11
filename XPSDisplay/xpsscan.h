#ifndef XPSSCAN_H
#define XPSSCAN_H

#include <QList>
#include <QTextStream>
#include <QDebug>
#include <QFile>

/// This defines a single XPS Scan, the information that will populate this class will come from an IGOR text file

class XPSScan
{


public:
    // Constructor
    XPSScan();

    // Loads IGOR text file and populates member variables. It finds the beginning of the data and fills the kineticEnergy and detectionCounts list.
    void loadFromFile(QString filePath);

    // Getters
    float I0() { return I0_; }
    float photonEnergy() { return photonEnergy_; }

    // Setters
    void setI0(float I0);
    void setPhotonEnergy(float energy);


private:
    // Both i0 and photonEnergy (hv) are manually entered
    // ToDo: Come up with a better name for I0
    float I0_;
    float photonEnergy_;

    // kineticEnergy and detectionCounts are populated by the IGOR text file
    QList<float> kineticEnergy_;
    QList<float> detectionCounts_;



};

#endif // XPSSCAN_H

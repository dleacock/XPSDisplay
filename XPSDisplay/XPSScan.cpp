#include "XPSScan.h"


XPSScan::XPSScan(qreal i0, qreal hv, QString filePath)
{

    incomingPhotons_ = i0;
    photonEnergy_ = hv;
    filePath_ = filePath;
    loadFromFile(filePath);


}

// Relevent data in IGOR file doesn't start until the head [Data 1] is displayed, the position of the header plus 14 spaces is where data starts.
// Its presented as kinetic energy followed by a single space then the counts.
void XPSScan::loadFromFile(QString filePath){

    QFile file(filePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream inputFile(&file);

    while(!inputFile.atEnd()){

    QString line = inputFile.readLine();
	if(line == ("[Data 1]")){

            while(!inputFile.atEnd()){
                 QString temp = inputFile.readLine();
		 // Last line of IGOR file is a blank space.
		 // ToDo: Test this out.
		 if(temp.isEmpty())
			 break;
		 else{
			 QStringList tempList = temp.split(" ", QString::SkipEmptyParts);
			 kineticEnergy_.append(tempList.at(0).toDouble());
			 detectionCounts_.append((tempList.at(1).toDouble()/incomingPhotons_));
		 }
	    }
        }
    }

    file.close();
    // Need to know number of points collected so the map knows how big to be
    numberOfPoints_ = kineticEnergy_.count();
}

void XPSScan::setI0(qreal incomingPhotons){
    incomingPhotons_ = incomingPhotons;
}

void XPSScan::setPhotonEnergy(qreal energy){
    photonEnergy_ = energy;
}




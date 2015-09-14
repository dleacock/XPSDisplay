#include "XPSScan.h"
#include "iostream"
#include "QRegExp"

XPSScan::XPSScan()
{
    //Testing purposes using generic data
    I0_ = 10.0;
    photonEnergy_ = 10.0;

}

/*
 *  loadFromFile parsing algorithm.
 *  1. Find the line containing [Data 1], for every file given this will always be the case that this header exists.
 *  2. Go to next line. This line and all lines after it until the end of the file will start will a few spaces, a number, a space then the last number.
 *  3. Find the first floating point number and store in the QVector kineticEnergy_
 *  4. Find the next floating point number and store in QVector detectionCounts_
 *
 *
*/
void XPSScan::loadFromFile(QString filePath){

    QFile file(filePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream inputFile(&file);

    while(!inputFile.atEnd()){

        // Relevent data in IGOR file doesn't start until the head [Data 1] is displayed, the position of the header plus 14 spaces is where data starts.
        // Its presented as kinetic energy followed by a single space then the counts.

        QString line = inputFile.readAll();
        // Start by finding the index of the header file. Add the length of that header file (8 spaces) and this provides the starting index of all the data needed.
        // As of sept 12 this finds all the numbers after the data header, without any regard for spacing or decimals. My current thinking is that I find the index of
        // the first number, find the index of the next space and store that index. Use substr (size_t pos = 0, size_t len = npos) to clip out the number, convert it
        // to qreal then store in vector. Repeat for next digit then on to the next line.

        int indexOfDataHeader = line.indexOf("[Data 1]");

        if( indexOfDataHeader != -1){

            QRegExp regNum("([0-9])");

            int indexFound = line.indexOf(regNum, indexOfDataHeader + 8);
            while(indexFound != -1){

                // Currently at beginning of important data. Grab current index. Find next space, grab that index
                int indexStartKinetic = indexFound;
                int indexEndKinetic = line.indexOf(" ", indexStartKinetic) - 1;
                QString kineticString = line.mid(indexStartKinetic, indexEndKinetic-indexStartKinetic + 1);

                // Jump to start of next group of numbers. Get index, find and store the last index
                int indexStartCounts = line.indexOf(regNum, indexEndKinetic + 1);
                int indexEndCounts = line.indexOf('\n', indexStartCounts) - 1;
                QString countsString = line.mid(indexStartCounts, indexEndCounts-indexStartCounts + 1);

                // Convert to double the store in vector
                qreal kineticEnergy = kineticString.toDouble();
                qreal counts = countsString.toDouble();

                kineticEnergy_.append(kineticEnergy);
                detectionCounts_.append(counts);

                // Update index then restart loop
                indexFound = line.indexOf(regNum, indexEndCounts+1);

            }
        }
    }

    file.close();
}


void XPSScan::setI0(qreal I0){
    I0_ = I0;
}

void XPSScan::setPhotonEnergy(qreal energy){
    photonEnergy_ = energy;
}




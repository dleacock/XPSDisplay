#include "XPSScan.h"
#include "iostream"
#include "QRegExp"
#include "QStringList"
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

        QString line = inputFile.readLine();
        // Start by finding the index of the header file. Add the length of that header file (8 spaces) and this provides the starting index of all the data needed.
        // As of sept 12 this finds all the numbers after the data header, without any regard for spacing or decimals. My current thinking is that I find the index of
        // the first number, find the index of the next space and store that index. Use substr (size_t pos = 0, size_t len = npos) to clip out the number, convert it
        // to qreal then store in vector. Repeat for next digit then on to the next line.

        if(line == ("[Data 1]")){

            while(!inputFile.atEnd()){
                 QString temp = inputFile.readLine();
                 QStringList tempList = temp.split(" ", QString::SkipEmptyParts);
                 kineticEnergy_.append(tempList.at(0).toDouble());
                 detectionCounts_.append((tempList.at(1).toDouble()/I0_));
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




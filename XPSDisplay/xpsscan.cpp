#include "xpsscan.h"
#include "iostream"

XPSScan::XPSScan()
{
    //Testing purposes using generic data
    I0_ = 10.0;
    photonEnergy_ = 10.0;

}

void XPSScan::loadFromFile(QString filePath){

    qDebug() << "entering loadFromFile" << endl;

    QFile file(filePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream inputFile(&file);

    while(!inputFile.atEnd()){

        // Relevent data in IGOR file doesn't start until the head [Data 1] is displayed, the position of the header plus 14 spaces is where data starts.
        // Its presented as kinetic energy followed by a single space then the counts.
        QString line = inputFile.readLine();

        //QString dataHeader = "[Data 1]";
        //int photonEnergyIndexPosition = line.indexOf(dataHeader) + 14;
        //QString copyText = line.right(photonEnergyIndexPosition);

        // Current testing goal, to simply output line by line the data without storing it first
        qDebug() << line << endl;

        // I might need to convert the QString to a std::string so I can use the standard librarys find functions to help parse
        //std::string copyTextString = copyText.toUtf8().constData();



    }
}


void XPSScan::setI0(float I0){
    I0_ = I0;
}

void XPSScan::setPhotonEnergy(float energy){
    photonEnergy_ = energy;
}




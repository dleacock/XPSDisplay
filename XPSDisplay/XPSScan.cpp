#include "XPSScan.h"
#include "iostream"

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

    qDebug() << "entering loadFromFile" << endl;

    QFile file(filePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream inputFile(&file);

    while(!inputFile.atEnd()){

        // Relevent data in IGOR file doesn't start until the head [Data 1] is displayed, the position of the header plus 14 spaces is where data starts.
        // Its presented as kinetic energy followed by a single space then the counts.

	QString line = inputFile.readAll();
	std::string lineString = line.toStdString();


	// Start by finding the index of the header file. Add the length of that header file (8 spaces) and this provides the starting index of all the data needed.
	// As of sept 12 this finds all the numbers after the data header, without any regard for spacing or decimals. My current thinking is that I find the index of
	// the first number, find the index of the next space and store that index. Use substr (size_t pos = 0, size_t len = npos) to clip out the number, convert it
	// to qreal then store in vector. Repeat for next digit then on to the next line.
	std::size_t indexOfDataHeader = lineString.find("[Data 1]");
	if( indexOfDataHeader != std::string::npos){

		std::size_t indexFound = lineString.find_first_of("0123456789", indexOfDataHeader + 8);
		while(indexFound != std::string::npos){

			// Currently at beginning of important data. Grab current index. Find next space, grab that index
			std::size_t indexStartKinetic = indexFound;
			std::size_t indexEndKinetic = lineString.find_first_of(" ", indexStartKinetic)-1;

			std::string kineticString = lineString.substr(indexStartKinetic, indexEndKinetic-indexStartKinetic+1);


			// Jump to start of next group of numbers. Get index, find and store the last index
			std::size_t indexStartCounts = lineString.find_first_of("0123456789", indexEndKinetic+1);
			std::size_t indexEndCounts = lineString.find_first_of('\n', indexStartCounts)-1;

			std::string countsString = lineString.substr(indexStartCounts, indexEndCounts-indexStartCounts+1);

			//DEBUG: output values
			std::cout << kineticString << " " << countsString << std::endl;

			//ToDo: Convert kineticString and countsString to qreal then store in vectors


			// Update index then restart loop
			indexFound = lineString.find_first_of("0123456789", indexEndCounts+1);

		}
	}


        // I might need to convert the QString to a std::string so I can use the standard librarys find functions to help parse
	//std::string copyTextString = copyText.toUtf8().constData();
    }

    file.close();
}


void XPSScan::setI0(qreal I0){
    I0_ = I0;
}

void XPSScan::setPhotonEnergy(qreal energy){
    photonEnergy_ = energy;
}




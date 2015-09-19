#include "XPSMapViewModel.h"


XPSMapViewModel::XPSMapViewModel()
{
	// I only want a XPSMapViewModel created after files have been selected to use. These functions will be used to create instances of QList<XPSScan> and XPSMap
	loadScansFromFiles();
	loadScanIntoMap();

}

// This will be provided a list (QString file names?) and iterater
// through each value on the list, create an XPS scan for each one
// then store it in the QList<XPSScan *>
void XPSMapViewModel::loadScansFromFiles()
{
	//Create QList<XPSScan *> here


}


void XPSMapViewModel::loadScanIntoMap()
{
	// Create XPSMap here

}


#ifndef XPSMAPVIEWMODEL_H
#define XPSMAPVIEWMODEL_H

#include "XPSMap.h"
#include "XPSMap.h"


// Allows for communcation between the individual XPS scans
// and the XPSMap. This class allows the XPSDisplayWidget to interact
// with the scans and maps

// Function will load xps scans and give them to xps map to create map
// This class is an interface between the two

// This is the first pass at writing this class. Functions aren't finished.
// Just determining what is required first.

// The XPSDisplayWidget will ask the model to load the scans into the map.
// The map will be given to the widget for display.


class XPSMapViewModel
{
public:
    XPSMapViewModel();

    // returns the file name of a particular xps scan. The widget will want to display this info
    QString scanName(int index);
    // returns the XPSMap to who requested it, in this case the XPSDisplayWidget
    XPSMap *map() const { return map_; }



    // create new xps scan from params and add it to QList<XPSScan>
    void loadScansFromFiles(qreal i0, qreal hv, QString fileName);
    // function will be iterated over all scans, it loads each scan into XPSMap class to build map
    void loadScanIntoMap();
    // remove a scan from the list as requested by the widget
    void removeScan();


private:
    // map that contains all the scan data it was provided
    XPSMap *map_;
    // List of xps scans to give to XPSMap
    QList<XPSScan *> scans_;

};

#endif // XPSMAPVIEWMODEL_H

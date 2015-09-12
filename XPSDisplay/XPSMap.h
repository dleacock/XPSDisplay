#ifndef XPSMAP_H
#define XPSMAP_H

#include "XPSScan.h"

class XPSMap
{

public:
	XPSMap();

	void buildXPSMap();
	QList<XPSScan> scans() { return scans_; }

private:
	QList<XPSScan> scans_;


};

#endif // XPSMAP_H

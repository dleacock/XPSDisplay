#include "main.h"
#include "XPSScan.h"
#include "XPSDisplayWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

    QString filePath = "/home/david/code/XPSDisplay/XPSDisplay/Au0001.txt";

	XPSScan *testScan = new XPSScan(10, 10, filePath);
	//testScan->loadFromFile(filePath);

	XPSDisplayWidget widget;
	widget.show();

	return app.exec();
}

#include "main.h"
#include "XPSScan.h"

int main()
{
  QString filePath = "/home/david/code/XPSDisplay/XPSDisplay/testData.txt";

  XPSScan *testScan = new XPSScan();

  testScan->loadFromFile(filePath);


  return 0;
}

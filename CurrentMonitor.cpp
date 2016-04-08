#include "CurrentMonitor.h"
#include "Calibration.h"

using namespace std;

CurrentMonitor::CurrentMonitor()
{
_desiredCurrent = 0;
}

// i: The desired current value in mA.
void CurrentMonitor::SetDesiredCurrent(unsigned int i)
{
_desiredCurrent = map(i,0,1000,0,4096);
analogWrite(isetPin, _desiredCurrent);
}

// Returns: The sense current from op amps
unsigned short int currentMonitor::ReadHiSenseCurrent()
{
calibrateAdc();
// Map current from ADC value to mA scale
return map((analogRead(isensePin) + gVoltageCalibrationOffset),0,4096,0,1000);
}

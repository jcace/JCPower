#include "VoltageMonitor.h"
//#include <stdint.h>

using namespace std;

VoltageMonitor::VoltageMonitor()
{
_currentVoltage = 0;
_desiredVoltage = 0;
_calibrationFactor = 0;
}

// Take the 2.048vref input and see if the ADC has is slightly off, adjust for it
// TODO: Allow reading back of output voltage for more precise calibration 
unsigned short int VoltageMonitor::CalibrateVoltage()
{
unsigned short int ref_2048 = analogRead(refPin);
_calibrationFactor = 2542 - ref_2048; // 2542 = 2.048/3.3 * 4096
}

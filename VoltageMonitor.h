#ifndef VoltageMonitor_h
#define VoltageMonitor_h
#include "application.h"

class VoltageMonitor
{
public:
VoltageMonitor();
unsigned short int CalibrateVoltage();

private:
unsigned short int _currentVoltage;
unsigned short int _desiredVoltage;
signed short int _calibrationFactor;

};

#endif

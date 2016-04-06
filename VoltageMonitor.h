#ifndef VoltageMonitor_h
#define VoltageMonitor_h
#include "application.h"
#include "main.h"

// The threshold (in mV) to enable the boost circuitry
#define BOOST_THRESHOLD 7200
class VoltageMonitor
{
public:
VoltageMonitor();
void CalibrateVoltage();
unsigned short int ReadVoltage();
void enableBoost(unsigned int v);
void setDesiredVoltage(unsigned int v);
private:
unsigned short int _currentVoltage;
unsigned short int _desiredVoltage;
signed short int _calibrationOffset;
signed short int _calibrationScale;
bool _boostEnabled;

};

#endif

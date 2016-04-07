#ifndef VoltageMonitor_h
#define VoltageMonitor_h
#include "application.h"
#include "main.h"

// The threshold (in mV) above battery voltage to enable the boost circuitry
#define BOOST_THRESHOLD 1000
#define EPOT_ADDRESS 47 // 0101111 as per MCP4017 datasheet
class VoltageMonitor
{
public:
VoltageMonitor();
void CalibrateVoltage();
unsigned short int ReadSenseVoltage();
void ReadBatteryVoltage();
void EnableBoost(unsigned int v);
void SetDesiredVoltage(unsigned int v);
private:
unsigned short int _currentVoltage;
unsigned short int _desiredVoltage;
unsigned short int _batteryVoltage;
signed short int _calibrationOffset;
signed short int _calibrationScale;
bool _boostEnabled;

};

#endif

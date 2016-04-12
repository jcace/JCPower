#ifndef VoltageMonitor_h
#define VoltageMonitor_h
#include "application.h"
#include "main.h"
#include "Calibration.h"

// The threshold (in mV) above battery voltage to enable the boost circuitry
#define BOOST_THRESHOLD 1000
#define EPOT_I2C_ADDRESS 47 // 0101111 as per MCP4017 datasheet
class VoltageMonitor
{
public:
VoltageMonitor();
void CalibrateVoltage();
unsigned short int ReadSenseVoltage();
unsigned short int ReadBatteryVoltage();
void SetDesiredVoltage(unsigned int v);

private:
void setBoost(unsigned int v);
unsigned short int _desiredVoltage;
unsigned short int _batteryVoltage;
signed short int gVoltageCalibrationOffset;
bool _boostEnabled;
};

#endif

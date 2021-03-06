#ifndef VoltageMonitor_h
#define VoltageMonitor_h
#include "application.h"
#include "main.h"
#include "Calibration.h"

// The threshold (in mV) above battery voltage to enable the boost circuitry
#define BOOST_THRESHOLD 1000
#define EPOT_I2C_ADDRESS 47 // 0101111 as per MCP4017 datasheet
#define DAC_CALIB_INTERCEPT -720
#define DAC_CALIB_SLOPE 0.9946
class VoltageMonitor
{
public:
VoltageMonitor();
void CalibrateVoltage();
unsigned int ReadSenseVoltage();
unsigned int ReadBatteryPercentage();
void SetDesiredVoltage(unsigned int v);

private:
void setBoost(unsigned int v);
unsigned int _desiredVoltage;
unsigned int _batteryVoltage;
unsigned int ReadBatteryVoltage();
signed int gVoltageCalibrationOffset;
bool _boostEnabled;
};

#endif

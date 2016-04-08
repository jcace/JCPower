#include "VoltageMonitor.h"
#include "application.h"
//#include <stdint.h>

using namespace std;

VoltageMonitor::VoltageMonitor()
{
_currentVoltage = 0;
_desiredVoltage = 0;
_calibrationOffset = 0;
_calibrationScale = 1; //TODO: Change this to double if needed
_boostEnabled = false;
ReadBatteryVoltage();
}

// Take the 2.048vref input and see if the ADC has is slightly off, adjust for it
// TODO: Allow reading back of output voltage for more precise calibration, use CalibrationScale.
void VoltageMonitor::CalibrateVoltage()
{
unsigned short int ref_2048 = analogRead(refPin);
_calibrationOffset = 2542 - ref_2048; // 2542 = 2.048/3.3 * 4096
}

// Read in the voltage from the VSENSE pin. Adjust for calibration value.
unsigned short int VoltageMonitor::ReadSenseVoltage() {
CalibrateVoltage();
return _calibrationScale*(analogRead(vsensePin) + _calibrationOffset);
}

unsigned short int VoltageMonitor::ReadBatteryVoltage()
{
CalibrateVoltage();
// Map battery voltage based on the resistor devider 0-14.20V max input
_batteryVoltage = map(_calibrationScale*(analogRead(bsensePin) + _calibrationOffset),0,4096,0,14200);
return _batteryVoltage;
}

// INPUT: v in 1mV steps (ie, 19620 for 19.620V)
// Note that hardware resolution is only ~5mV, so will be rounded accordingly
void VoltageMonitor::SetDesiredVoltage(unsigned int v)
{
  // Map the voltage request over to a DAC value.
_desiredVoltage = map(v,0,19620,0,4096);

// Ensure the battery voltage reading is up to date.
ReadBatteryVoltage();
if ((v + BOOST_THRESHOLD) > _batteryVoltage)
{
  _boostEnabled = true;
  setBoost(v);
  digitalWrite(boostPin, HIGH);
}
else
{
  _boostEnabled = false;
  digitalWrite(boostPin,LOW);
}
// Write the desired voltage on the DAC output
analogWrite(vsetPin,v);
}

void VoltageMonitor::setBoost(unsigned int v)
{
// Calculate required resistance precisely, based on V
double desiredResistance = (1804000*v - 39684960) / (15128 - 2200*v);
// Determine the value to write into the epot - round down for worst-case scenario
uint8_t resistanceBytes = ((int) desiredResistance / 127) - 1);

if (resistanceBytes > 127)
  resistanceBytes = 127;

Wire.beginTransmission(EPOT_I2C_ADDRESS)
Wire.write(resistanceBytes);
}

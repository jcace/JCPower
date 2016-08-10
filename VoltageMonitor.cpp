#include "VoltageMonitor.h"
//#include <stdint.h>

using namespace std;

VoltageMonitor::VoltageMonitor()
{
_desiredVoltage = 0;
_boostEnabled = false;
ReadBatteryVoltage();
}

// Read in the voltage from the VSENSE pin. Adjust for calibration value.
unsigned int VoltageMonitor::ReadSenseVoltage() {
calibrateAdc();
int v = map(analogRead(vsensePin),0,4095,0,19800); //+ gVoltageCalibrationOffset;
return v;
}

unsigned int VoltageMonitor::ReadBatteryPercentage()
{
  float perc =  (float)(ReadBatteryVoltage() - 5600) / 2800;
  // Ensure battery percentage is capped at 0 and 100%
  if (perc < 0)
    perc = 0;
  else if (perc > 1.00)
    perc = 1.00;

    // TODO: Seems to return 100% when perc is less than zero (ie, below minimum threshold)
  return (unsigned int) (perc * 100);
}
unsigned int VoltageMonitor::ReadBatteryVoltage()
{
calibrateAdc();
// Map battery voltage based on the resistor devider 0-14.20V max input
float battVoltage = (float)map((analogRead(bsensePin) + gVoltageCalibrationOffset),0,4095,0,14200);
battVoltage *= 1.031;
battVoltage -= 138.5;
_batteryVoltage = (unsigned int) battVoltage;
return _batteryVoltage;
}

// INPUT: v in 1mV steps (ie, 19620 for 19.620V)
// Note that hardware resolution is only ~5mV, so will be rounded accordingly
void VoltageMonitor::SetDesiredVoltage(unsigned int v)
{
  // Add hand-calibration values to make the voltage output more accurate
  float vCalc = ((float)v * DAC_CALIB_SLOPE) + DAC_CALIB_INTERCEPT;

  // Map the voltage request over to a DAC value.
_desiredVoltage = map((unsigned int)vCalc,0,19800,0,4095);

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
analogWrite(vsetPin, _desiredVoltage);
}

void VoltageMonitor::setBoost(unsigned int v)
{
// Calculate required resistance precisely, based on V
int voltz = v/1000;

double desiredResistance = (1804000*voltz - 39684960) / (15128 - 2200*voltz);
// Determine the value to write into the epot - round down for worst-case scenario
uint8_t resistanceBytes = (uint8_t) (((int) desiredResistance / 127) - 1);

if (resistanceBytes > 127)
  resistanceBytes = 127;

Wire.beginTransmission(EPOT_I2C_ADDRESS);

Wire.write(resistanceBytes);

Wire.endTransmission();
}

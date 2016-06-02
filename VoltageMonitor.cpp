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
unsigned short int VoltageMonitor::ReadSenseVoltage() {
calibrateAdc();
return analogRead(vsensePin) + gVoltageCalibrationOffset;
}

unsigned short int VoltageMonitor::ReadBatteryVoltage()
{
calibrateAdc();
// Map battery voltage based on the resistor devider 0-14.20V max input
_batteryVoltage = map((analogRead(bsensePin) + gVoltageCalibrationOffset),0,4096,0,14200);
return _batteryVoltage;
}

// INPUT: v in 1mV steps (ie, 19620 for 19.620V)
// Note that hardware resolution is only ~5mV, so will be rounded accordingly
void VoltageMonitor::SetDesiredVoltage(unsigned int v)
{
  // Map the voltage request over to a DAC value.
_desiredVoltage = map(v,0,19620,0,4096);

// Ensure the battery voltage reading is up to date.
Serial.println("v =");
Serial.println(_desiredVoltage);

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

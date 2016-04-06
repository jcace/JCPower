#include "VoltageMonitor.h"
#include "application.h"
//#include <stdint.h>

using namespace std;

VoltageMonitor::VoltageMonitor()
{
_currentVoltage = 0;
_desiredVoltage = 0;
_calibrationOffset = 0;
_calibrationScale = 1;
_boostEnabled = false;
}

// Take the 2.048vref input and see if the ADC has is slightly off, adjust for it
// TODO: Allow reading back of output voltage for more precise calibration, use CalibrationScale.
void VoltageMonitor::CalibrateVoltage()
{
unsigned short int ref_2048 = analogRead(refPin);
_calibrationOffset = 2542 - ref_2048; // 2542 = 2.048/3.3 * 4096
}

// Read in the voltage from the VSENSE pin. Adjust for calibration value.
unsigned short int VoltageMonitor::ReadVoltage() {
CalibrateVoltage();
return _calibrationScale*(analogRead(vsensePin) + _calibrationOffset);
}

// INPUT: v in 1mV steps (ie, 19620 for 19.620V)
// Note that hardware resolution is only ~5mV, so will be rounded accordingly
void VoltageMonitor::setDesiredVoltage(unsigned int v)
{
  // Map the voltage request over to a DAC value.
_desiredVoltage = map(v,0,19620,0,4096);

if (v > BOOST_THRESHOLD)
{
  _boostEnabled = true;
  enableBoost(v);
}
else
{
  _boostEnabled = false;
  digitalWrite(boostPin,LOW);
}
}

void VoltageMonitor::enableBoost(unsigned int v)
{
digitalWrite(boostPin, HIGH);
return;
// TODO: Talk to the E2POT and set the desired resistance
// Also enable the BOOST pin.
}

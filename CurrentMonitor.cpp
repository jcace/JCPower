#include "CurrentMonitor.h"
#include "Calibration.h"

using namespace std;

CurrentMonitor::CurrentMonitor()
{
  ina219.begin();
_desiredCurrent = 0;
}

// i: The desired current value in mA, from 0-1000
void CurrentMonitor::SetDesiredCurrent(unsigned int i)
{
_desiredCurrent = map(i,0,1000,0,4095);
//Serial.println("desired current:");
//Serial.println(_desiredCurrent);
analogWrite(isetPin, _desiredCurrent);
}

// Returns: The sense current from op amps
int CurrentMonitor::ReadHiSenseCurrent()
{
calibrateAdc();
// Map current from ADC value to mA scale
return map(analogRead(isensePin) + gVoltageCalibrationOffset,0,4095,0,1000);
}
// TODO: Change the current gain register to provide mode accurate measurements
int CurrentMonitor::ReadSenseCurrent()
{
  float current_mA = ina219.getCurrent_mA();

  if (current_mA >= 320.00)
  {
  return ReadHiSenseCurrent();
  }
  else
  {
  return int(current_mA+0.5);
  }
}

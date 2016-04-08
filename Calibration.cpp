#include "Calibration.h"

using namespace std;

signed short int gVoltageCalibrationOffset = 0;

// Take the 2.048vref input and see if the ADC has is slightly off, adjust for it
// TODO: Allow reading back of output voltage for more precise calibration, use CalibrationScale.
signed short int calibrateAdc()
{
  unsigned short int ref_2048 = analogRead(refPin);
  gVoltageCalibrationOffset = 2542 - ref_2048; // 2542 = 2.048/3.3 * 4096
}

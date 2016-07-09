#ifndef CurrentMonitor_h
#define CurrentMonitor_h
#include "application.h"
#include "main.h"
#include "ina129Spark.h"


#define INA219_I2C_ADDRESS 64 // "1000000"

class CurrentMonitor
{
public:
CurrentMonitor();
void SetDesiredCurrent(unsigned int i);
int ReadSenseCurrent();

private:
uint16_t _desiredCurrent;
bool _usingMicroCurrent;
Adafruit_INA219 ina219;
int ReadHiSenseCurrent();
};
#endif

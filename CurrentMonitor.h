#ifndef CurrentMonitor_h
#define CurrentMonitor_h
#include "application.h"
#include "main.h"

#define INA219_I2C_ADDRESS 64 // "1000000"

class CurrentMonitor
{
public:
CurrentMonitor();
void SetDesiredCurrent(unsigned int i);

private:
uint8_t _desiredCurrent;
bool _usingMicroCurrent;
};
#endif

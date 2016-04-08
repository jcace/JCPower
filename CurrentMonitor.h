#ifndef CurrentMonitor_h
#define CurrentMonitor_h
#include "application.h"
#include "main.h"

class CurrentMonitor
{
public:
CurrentMonitor();
void SetDesiredCurrent(unsigned int i);

private:
uint8_t _desiredCurrent;
};
#endif

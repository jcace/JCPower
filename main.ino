#include "main.h"
#include "VoltageMonitor.h"
#include "CurrentMonitor.h"

VoltageMonitor volt;
CurrentMonitor curr;
bool _isEnabled;
unsigned long lastTime = 0UL;
void setup() {

pinMode(refPin, INPUT);
pinMode(vsetPin, OUTPUT);
pinMode(bsensePin,INPUT);
pinMode(isensePin, INPUT);
pinMode(vsensePin, INPUT);
pinMode(isetPin, OUTPUT);
pinMode(buzzerPin, OUTPUT);
pinMode(heartbeatLedPin, OUTPUT);
// D0 - SDA, D1 - SCL
pinMode(ilimPin, INPUT);
pinMode(boostPin, OUTPUT);

  // Initialize Serial communication
  Serial.begin(9600);
  Serial.println(WiFi.localIP());
  Time.zone(-7);
  Spark.syncTime();

  // Initialize I2C Communication
   Wire.begin();

   volt.SetDesiredVoltage(0);
   curr.SetDesiredCurrent(0);

   tone(buzzerPin,1000,400);
   delay (400);
   tone(buzzerPin, 1200, 400);

   // Declare the Spark function for cloud connectivity.
   Spark.function("webset",WebSet);
   _isEnabled = false;

 }

void loop()
{
  unsigned long now = millis();
  if (now-lastTime>1000UL) {
      digitalWrite(heartbeatLedPin, !digitalRead(heartbeatLedPin));
          lastTime = now;
          float currentCurrent = curr.ReadSenseCurrent();
          int currentVoltage = volt.ReadSenseVoltage();
          // now is in milliseconds
          char publishString[100];
          sprintf(publishString,"{\"v\":%d,\"c\":%f, \"b\":%d}", currentVoltage, currentCurrent, volt.ReadBatteryPercentage());
          Spark.publish("Stats",publishString);

          #if DEBUG_SERIAL
            Serial.print("Current: ");
            Serial.print(currentCurrent);
            Serial.print(" Voltage: ");
            Serial.print(currentVoltage);
            Serial.println("");
          #endif
      }
}

int WebSet(String command) {
  int c, v = 0;
    bool enable = false;
    // Copy the command string to an array of chars, split based on "-" characters
    char * params = new char[command.length() + 1];
    strcpy(params, command.c_str());
    char * p = strtok(params, "-");

// Step through each of the command settings.
int commandStep = 0;
while (p != NULL)
{
  Serial.println(p);
  if (commandStep == 0)
  {
    v = atoi(p); // Voltage setting in mV
  }
  if (commandStep == 1)
  {
    c = atoi(p); // Current setting in mA
  }
  if (commandStep == 2)
  {
    if (strcmp(p,"true") == 0)
    {
      enable = true;
    }
    else
      enable = false;
  }
  p = strtok(NULL, "-");
  commandStep++;
}

if (!enable)
  {
  _isEnabled = false;
  curr.SetDesiredCurrent(0);
  volt.SetDesiredVoltage(0);
  return 0;
  }
  else
  {
    _isEnabled = true;
    curr.SetDesiredCurrent(c);
    volt.SetDesiredVoltage(v);
    return 1;
  }
  return 1;
}

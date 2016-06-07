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

   volt.SetDesiredVoltage(2000);
   curr.SetDesiredCurrent(1000);

   tone(buzzerPin,1000,400);
   delay (400);
   tone(buzzerPin, 1200, 400);

   // Declare the Spark function for cloud connectivity.
   Spark.function("webset",WebSet);
   _isEnabled = true;

 }

void loop()
{
  unsigned long now = millis();
    if (now-lastTime/500UL > 1UL)
    {
  digitalWrite(heartbeatLedPin, !digitalRead(heartbeatLedPin));
  volt.SetDesiredVoltage(19800);
  curr.SetDesiredCurrent(200);
  Serial.println("current:");
  Serial.println(curr.ReadSenseCurrent());
    }
  //Serial.println("voltage:");
  //Serial.println(volt.ReadSenseVoltage());
  //Serial.println("vbat:");
  //Serial.println(volt.ReadBatteryVoltage());
  if (now-lastTime>5000UL) {
          lastTime = now;
          // now is in milliseconds
          char publishString[100];
          sprintf(publishString,"{\"v\":%d,\"c\":%d}", volt.ReadSenseVoltage(), curr.ReadSenseCurrent());
          Spark.publish("Stats",publishString);
      }
}

int WebSet(String command) {
  int c, enable, v = 0;
    // Copy the command string to an array of chars, split based on "-" characters
    char * params = new char[command.length() + 1];
    strcpy(params, command.c_str());
    char * p = strtok(params, "-");

// Step through each of the command settings.
int commandStep = 0;
while (p != NULL)
{
  if (commandStep = 0)
  {
    int enable = atoi(p); // Enable setting, 1 = output, 0 = off.
    enable = atoi(p); // Enable setting, 1 = output, 0 = off.
  }
  if (commandStep = 1)
  {
    int voltage = atoi(p);
    v = atoi(p); // Voltage setting in mV
  }
  if (commandStep = 2)
  {
    int current = atoi(p);
    c = atoi(p); // Current setting in mA
  }
}
if (enable != 1)
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
    volt.SetDesiredVoltage(v); // TODO: Handle the type conversions here
    return 1;
  }
  return 1; // TODO: return 0, return -1 for errors?
}

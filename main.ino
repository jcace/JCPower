#include "main.h"
#include "VoltageMonitor.h"
#include "CurrentMonitor.h"

VoltageMonitor volt;
CurrentMonitor curr;

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
   curr.SetDesiredCurrent(1);

   tone(buzzerPin,1000,400);
   delay (400);
   tone(buzzerPin, 1200, 400);
 }

void loop()
{
  digitalWrite(heartbeatLedPin, HIGH);
  delay (500);
  digitalWrite(heartbeatLedPin, LOW);
  delay (500);

  volt.SetDesiredVoltage(2000);
  curr.SetDesiredCurrent(1000);

  Serial.println("voltage:");
  Serial.println(volt.ReadSenseVoltage());
  Serial.println("current:");
  Serial.println(curr.ReadSenseCurrent());
  Serial.println("vbat:");
  Serial.println(volt.ReadBatteryVoltage());
}

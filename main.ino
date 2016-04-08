#include "main.h"
void setup() {

pinMode(refPin, INPUT);
pinMode(vsetPin, OUTPUT);
pinMode(bsensePin,INPUT);
pinMode(isensePin, INPUT);
pinMode(vsensePin, INPUT);
pinMode(isetPin, OUTPUT);
pinMode(buzzerPin, OUTPUT);
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

  // Play a 100ms tone to indiate powerup
  tone(buzzerPin,330,100);
  delay(100);
}

void loop()
{

}

#include "main.h"
void setup() {

pinMode(refPin, INPUT);
pinMode(vsetPin, OUTPUT);
pinMode(bsensePin,INPUT);
pinMode(A1,INPUT); // ISENSE
pinMode(vsensePin, INPUT);
pinMode(D6,OUTPUT); //DAC pin? ISET
pinMode(buzzerPin, OUTPUT);
// D0 - SDA, D1 - SCL

pinMode(D2,INPUT); //ILIM
pinMode(boostPin, OUTPUT); //BOOST

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

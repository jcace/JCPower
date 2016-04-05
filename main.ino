#define buzzerPin = D7;
#define refPin = A4;
void setup() {

pinMode(A4, INPUT); // 2.048VREF
pinMode(A3,OUTPUT); //VSET
pinMode(A2,INPUT); //BSENSE
pinMode(A1,INPUT); //ISENSE
pinMode(A0,INPUT); //VSENSE
pinMode(D6,OUTPUT); //DAC pin? ISET
pinMode(buzzerPin,OUTPUT); //WKP Pin? Buzzer
//D0 - SDA, D1 - SCL

pinMode(D2,INPUT); //ILIM
pinMode(D3,OUTPUT); //BOOST

  Serial.begin(9600);
  Serial.println(WiFi.localIP());
  Time.zone(-7);
  Spark.syncTime();

  //Play a 100ms tone to indiate powerup
  tone(buzzerPin,330,100);
  delay(100);
}

void loop()
{

}

/*
  Maxbotix simple test

  Instructions:
  - At least one of: (comment the appropriate code below)
    * PW is digital pin 8
    * TX is digital pin 6
    * AN is analog pin A0
  - Change code below according to your model (LV, XL and
  HRLV supported)

  Note:
  For convenience, the getRange method will always return centimeters.
  You can use convert fuctions to convert to another unit (toInches and
  toCentimeters are available)

*/
#include "Maxbotix.h"

Maxbotix rangeSensorPW(8, Maxbotix::PW, Maxbotix::LV);
Maxbotix rangeSensorTX(6, Maxbotix::TX, Maxbotix::LV);
Maxbotix rangeSensorAD(A0, Maxbotix::AN, Maxbotix::LV);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  unsigned long start;
  
  Serial.println("Reading...");
  
  // PW
  start = millis();
  Serial.print("PW: ");
  Serial.print(rangeSensorPW.getRange());
  Serial.print("cm - ");
  Serial.print(millis() - start);
  Serial.println("ms");
  
  // TX
  start = millis();
  Serial.print("TX: ");
  Serial.print(rangeSensorTX.getRange());
  Serial.print("cm - ");
  Serial.print(millis() - start);
  Serial.println("ms");
  
  // AD
  start = millis();
  Serial.print("AD: ");
  Serial.print(rangeSensorAD.getRange());
  Serial.print("cm - ");
  Serial.print(millis() - start);
  Serial.println("ms");
  
  Serial.println();
  delay(5000);
}

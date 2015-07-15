/*
  Maxbotix advanced test

  Instructions:
  - Same as simple test

  Filters:
  * NONE (default): No filtering
  * MEDIAN: Take the median of a sample
  * HIGHEST_MODE: Take the mode of a sample. In case more than
  one mode, the highest one is returned
  * LOWEST_MODE: Take the mode of a sample. In case more than
  one mode, the lowest one is returned
  * BEST: Take the mode of a sample. In case more than one
  mode is found, the median is returned
  * SIMPLE: Continue reading until sample_size consecutive readings
  are issued

*/
#include "Maxbotix.h"

Maxbotix rangeSensorPW(8, Maxbotix::PW, Maxbotix::LV, Maxbotix::BEST);

#ifdef MAXBOTIX_WITH_SOFTWARE_SERIAL
  Maxbotix rangeSensorTX(6, Maxbotix::TX, Maxbotix::LV, Maxbotix::MEDIAN);
#endif

Maxbotix rangeSensorAD(A0, Maxbotix::AN, Maxbotix::LV, Maxbotix::BEST, 9);

void setup()
{
  Serial.begin(9600);
  // Set the delay between AD readings to 10ms
  rangeSensorAD.setADSampleDelay(10);
}

void loop()
{
  unsigned long start;
  
  Serial.println("Reading...");
  
  // PW
  start = millis();
  Serial.print("PW (BEST): ");
  Serial.print(rangeSensorPW.getRange());
  Serial.print("cm - ");
  Serial.print(millis() - start);
  Serial.print("ms - ");
  printArray(rangeSensorPW.getSample(), rangeSensorPW.getSampleSize());
  Serial.print(" - Highest Mode: ");
  Serial.print(rangeSensorPW.getSampleMode(true));
  Serial.print(" - Lowest Mode: ");
  Serial.print(rangeSensorPW.getSampleMode(false));
  Serial.print(" - Median: ");
  Serial.print(rangeSensorPW.getSampleMedian());
  Serial.print(" - Best: ");
  Serial.print(rangeSensorPW.getSampleBest());
  Serial.println();
  
  #ifdef MAXBOTIX_WITH_SOFTWARE_SERIAL
    // TX
    start = millis();
    Serial.print("TX (MEDIAN): ");
    Serial.print(rangeSensorTX.getRange());
    Serial.print("cm - ");
    Serial.print(millis() - start);
    Serial.print("ms - ");
    printArray(rangeSensorTX.getSample(), rangeSensorTX.getSampleSize());
    Serial.print(" - Highest Mode: ");
    Serial.print(rangeSensorTX.getSampleMode(true));
    Serial.print(" - Lowest Mode: ");
    Serial.print(rangeSensorTX.getSampleMode(false));
    Serial.print(" - Median: ");
    Serial.print(rangeSensorTX.getSampleMedian());
    Serial.print(" - Best: ");
    Serial.print(rangeSensorTX.getSampleBest());
    Serial.println();
  #endif
  
  // AD
  start = millis();
  Serial.print("AD (BEST): ");
  Serial.print(rangeSensorAD.getRange());
  Serial.print("cm - ");
  Serial.print(millis() - start);
  Serial.print("ms - ");
  printArray(rangeSensorAD.getSample(), rangeSensorAD.getSampleSize());
  Serial.print(" - Highest Mode: ");
  Serial.print(rangeSensorAD.getSampleMode(true));
  Serial.print(" - Lowest Mode: ");
  Serial.print(rangeSensorAD.getSampleMode(false));
  Serial.print(" - Median: ");
  Serial.print(rangeSensorAD.getSampleMedian());
  Serial.print(" - Best: ");
  Serial.print(rangeSensorAD.getSampleBest());
  Serial.println();
  
  Serial.println();
  delay(5000);
}

void printArray(float* array, uint8_t array_size) {
  Serial.print("[");
  for (int i = 0; i < array_size; i++) {
    Serial.print(array[i]);
    if (i != array_size - 1) {
      Serial.print(", ");
    }
  }
  Serial.print("]");
}

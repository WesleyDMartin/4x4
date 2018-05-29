#include "Adafruit_VL53L0X.h"
#include <stdbool.h> 
#include <stdio.h>
#include <string.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void andHIGH(void);
void andLOW(void);
void outputInformation(int readSensor);


#define kAND_Signal  5
#define kLED 6
#define kDelay 1

// Project Ceilings
#define MAX_DIST 1000
#define MIN_DIST 50

#define kOutOfRange 4



void setup() {
  Serial.begin(9600);
  pinMode(kAND_Signal, OUTPUT); 
    delay(kDelay);
  pinMode(kLED, OUTPUT); 
    delay(kDelay);
  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(kDelay);
  }
  
  Serial.println("Adafruit VL53L0X test");
    delay(kDelay);
   andHIGH();
    delay(kDelay);
  if (!lox.begin()) {
    Serial.println(F("Failed to boot Sensor"));
    while(1);
  }   
  delay(kDelay);
  Serial.println("Sensor Activated");
  
 Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}

void andHIGH(void)
{   
  digitalWrite(kAND_Signal,HIGH);  // Activate Sensor 1
  delay(kDelay);   
  
 // digitalWrite(kLED,HIGH); // LED
    delay(kDelay);
}

void andLOW(void)
{   
  digitalWrite(kAND_Signal,LOW);  // Activate Sensor 1
  delay(kDelay);   
  
  // digitalWrite(kLED,LOW); // LED
    delay(kDelay);
}


void outputInformation(int readSensor)
{
   char currentReading[20] = "";


    sprintf(currentReading, "%03dA", readSensor);
    Serial.println( currentReading );  
}
  

void loop() 
{
  VL53L0X_RangingMeasurementData_t measure;

  int valueRead = 0;
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!  
  valueRead = measure.RangeMilliMeter;
  

  delay(kDelay);
}




#include "Adafruit_VL53L0X.h"
#include <stdbool.h> 
#include <stdio.h>
#include <string.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void activateSensor1(void);
void activateSensor2(void);
void outputInformation(int readSensor1, int readSensor2);


#define kSensor1SHUTDOWN 4
#define kSensor2SHUTDOWN 5
#define kLED 6
#define kDelay 50

// Project Ceilings
#define MAX_DIST 1000
#define MIN_DIST 7

#define kOutOfRange 4


int currentSensor = 1; 
int value1 = -1;
int value2 = -1;

void setup() {
  Serial.begin(9600);
  pinMode(kSensor2SHUTDOWN, OUTPUT); 
  pinMode(kSensor1SHUTDOWN, OUTPUT); 
  pinMode(kLED, OUTPUT); 
    delay(kDelay);
  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(kDelay);
  }
  
  Serial.println("Adafruit VL53L0X test");
  activateSensor1();
  if (!lox.begin()) {
    Serial.println(F("Failed to boot Sensor 2"));
    while(1);
  }   

  activateSensor2();

  delay(kDelay);
  
 Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}

void activateSensor1(void)
{   
  digitalWrite(kSensor2SHUTDOWN,HIGH);  // Activate Sensor 1
  delay(kDelay);   
  digitalWrite(kSensor1SHUTDOWN,LOW);  // Deactivate Sensor 2
  delay(kDelay);
  if (!lox.begin()) {
    Serial.println(F("Failed to boot Sensor 1"));
    while(1);
  } 
  digitalWrite(kLED,HIGH); // LED
    delay(kDelay);
}

void activateSensor2(void)
{

  digitalWrite(kSensor2SHUTDOWN,LOW);
  delay(kDelay);
  digitalWrite(kSensor1SHUTDOWN,HIGH);
  delay(kDelay);
  if (!lox.begin()) {
    Serial.println(F("Failed to boot Sensor 2"));
    while(1);
  } 

  pinMode(kLED, OUTPUT); 
  digitalWrite(kLED,LOW); // LED 
    delay(kDelay);
}

void outputInformation(int readSensor1, int readSensor2)
{
   char currentReading[20] = "";


    sprintf(currentReading, "%03dA%03dB", readSensor1 ,readSensor2);
    Serial.println( currentReading );  
}
  

void loop() 
{
  VL53L0X_RangingMeasurementData_t measure;

  int valueRead = 0;
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!  

  if ( currentSensor == 1) // I'm working with LED 1 then 
  {
      activateSensor2();
      valueRead = measure.RangeMilliMeter;
      currentSensor = 2;
      
      if (measure.RangeStatus != kOutOfRange)
      {
        if ((valueRead <= MAX_DIST) && (valueRead > MIN_DIST))
        { 
          value2 = valueRead;
        }
        else
        {
           value2 = 0;
        }       
      }   
      else
      {
        value2 = 0;
      }
      value1 = -1;

  }
  else
  {
      activateSensor1();
      valueRead = measure.RangeMilliMeter;      
      currentSensor = 1;
      if (measure.RangeStatus != kOutOfRange)
      {
        if ((valueRead <= MAX_DIST) && (valueRead > MIN_DIST))
        { 
          value1 = valueRead;
        }
        else
        {
           value1 = 0;
        }
      }   
      else
      {
        value1 = 0;        
      }
  }

  if ((value1 != -1) && (value2 != -1))
  {
     outputInformation(value1, value2);
     value1 = -1;
     value2 = -1; 
  }

  delay(kDelay);
}

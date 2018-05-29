#pragma once

#pragma warning (disable: 4996)

// #define realDeal
#define fakeTest

// Project Ceilings
#define NUMBER_OF_SENSORS 2
#define LEFT_SENSOR 0
#define RIGHT_SENSOR 1


// Process Method Parameters 
#define READ_BUFFER_SIZE 7
#define MAJORITY_THRESHOULD 0.5
#define DISTANCE_DELTA 30

#define MINIMUM_DISTANCE_FOR_HIGH 60
#define MAXIMUM_DISTANCE_FOR_HIGH 500 

// Status Constants
#define HIGH 1
#define LOW 0
#define EMPTY -1



typedef struct
{
	int currentHighLow;
	int previousHighLow;
	double currentDistance; 
	double previousDistance; 
} sensorStatusType;



class GestureTracker
{
private: 
	sensorStatusType sensorStatus[NUMBER_OF_SENSORS]; 
	int buffer_HighLow[NUMBER_OF_SENSORS][READ_BUFFER_SIZE];
	double buffer_Distance[NUMBER_OF_SENSORS][READ_BUFFER_SIZE];
	int bufferIndex; 
	bool readyToIdentify; 

public: 
	GestureTracker();
	~GestureTracker();
	void ProcessBuffer(void);
	void ParseReading(int sensorsInput[]);
	void ParseReading(char * sensorsInputStr);
	int IdentifyGesture(void);
};
/*
*	FILE		  : testing.cpp
*   PROJECT		  :	4X4
*   PROGRAMMER	  : Felipe Flor, Kalvin Stares, Wesley Martin, Ricardo Mohammed
*	FIRST VERSION : 4/17/2018
*	DESCRIPTION	  : This project is the quick demo of our prototype concept for a spastic
*	gesture interpreter, completed for the 4x4 challenge at Conestoga College, for which we
*	won first place.
*/

#include "GestureTracker.h"

#ifdef fakeTest

#include <string.h>
#include  "randomNum.h"

#include <stdio.h>


#define NUMBER_OF_FAKIES 20

void createTestCase(char fakeSensorsInputStr[][500]);

int main(void)
{
	// Set the seed 
	srand((unsigned int)time(NULL));
	GestureTracker gesture; 
	char fakeSensorsInputStr[NUMBER_OF_FAKIES][500] = { "" };
	createTestCase(fakeSensorsInputStr);

	int fakeIndex = 0; 
	int i = 0; 
	while (1)
	{	
		int sensorsInput[NUMBER_OF_SENSORS] = { 0 };
		sensorsInput[LEFT_SENSOR] = getRandomNumber(0, 500);
		sensorsInput[RIGHT_SENSOR] = getRandomNumber(0, 500);
			
		char sensorsInputStr[500] = "";
		sprintf(sensorsInputStr, "%03dA%03dB", sensorsInput[0], sensorsInput[1]);


		fakeIndex++; 
		if (fakeIndex >= NUMBER_OF_FAKIES)
		{
			fakeIndex = 0; 
		}
		printf("%s\n", sensorsInputStr);
		gesture.ParseReading(sensorsInputStr);
		//gesture.ParseReading(sensorsInputStr);
		gesture.IdentifyGesture();
	}


	return 0;
	


}

// Just some dummy data to get the test running
void createTestCase(char fakeSensorsInputStr[][500])
{
	int fakeSensorValues[NUMBER_OF_FAKIES][NUMBER_OF_SENSORS] =
	{
		{70, 0},
		{120,0},
		{170,0},
		{ 0, 80 },
		{ 0, 90 },

		{ 70, 0 },
		{ 120,0 },
		{ 170,0 },
		{ 0, 80 },
		{ 0, 90 },

		{ 120,0 },
		{0, 80},
		{ 0, 90 },
		{ 0, 140 },
		{ 0, 250 },

		{ 120,0 },
		{ 0, 80 },
		{ 0, 90 },
		{ 0, 140 },
		{ 0, 250 },
	};

	for (int i = 0; i < NUMBER_OF_FAKIES; i++)
	{
		sprintf(fakeSensorsInputStr[i], "%03dA%03dB", fakeSensorValues[i][0], fakeSensorValues[i][1]);
	}

	printf("");
}

#endif
/*
*	FILE		  : GestureTracker.cpp
*   PROJECT		  :	4X4
*   PROGRAMMER	  : Wesley Martin, Felipe Flor, Ricardo Mohammed
*	FIRST VERSION : 3/2017
*/

#include <stdio.h>
#include "GestureTracker.h"
#include <assert.h>
#include <string.h>
#include <math.h>
#include<windows.h>

GestureTracker::GestureTracker()
{
	int i = 0;

	for (i = 0; i < NUMBER_OF_SENSORS; i++)
	{
		sensorStatus[i].currentHighLow = EMPTY;
		sensorStatus[i].currentHighLow = EMPTY;
		sensorStatus[i].previousHighLow = EMPTY;
		sensorStatus[i].previousHighLow = EMPTY;


		sensorStatus[i].currentDistance = EMPTY;
		sensorStatus[i].currentDistance = EMPTY;
		sensorStatus[i].previousDistance = EMPTY;
		sensorStatus[i].previousDistance = EMPTY;

		int j = 0; 
		for (j = 0; j < READ_BUFFER_SIZE; j++)
		{
			buffer_HighLow[i][j] = EMPTY;
			buffer_Distance[i][j] = EMPTY;
		}
	}
	
	bufferIndex = 0;
	readyToIdentify = false; 

}

GestureTracker::~GestureTracker()
{
	printf("gestureTracker: Bye bye\n");
}

void GestureTracker::ProcessBuffer(void)
{
	bufferIndex = 0;
	int sensorIndex = 0;
	int sum[NUMBER_OF_SENSORS] = { 0 };

	double distanceSum = 0;
	int averageCount = 0;

	for (sensorIndex = 0; sensorIndex < NUMBER_OF_SENSORS; sensorIndex++)
	{
		for (bufferIndex = 0; bufferIndex < READ_BUFFER_SIZE; bufferIndex++)
		{
			// HIGH LOW  processing 
			// Get the amount of HIGHS in the Buffer for each sensor. 
			if (buffer_HighLow[sensorIndex][bufferIndex] == HIGH)
			{
				sum[sensorIndex] += 1;
			}

			assert(buffer_HighLow[sensorIndex][bufferIndex] != EMPTY);
			buffer_HighLow[sensorIndex][bufferIndex] = EMPTY;


			// AVERAGE DISTANCE processing 
			if (buffer_Distance[sensorIndex][bufferIndex] != EMPTY)
			{
				averageCount++;
				distanceSum += buffer_Distance[sensorIndex][bufferIndex];
				buffer_Distance[sensorIndex][bufferIndex] = EMPTY; 
			}
		}
	}	

	// If no distance was added. The sensors were not triggered in this iteration. 
	if (averageCount < (int) (NUMBER_OF_SENSORS*READ_BUFFER_SIZE * MAJORITY_THRESHOULD))
	{
		distanceSum = EMPTY;
	}

	// Set current and previous distances 
	for (sensorIndex = 0; sensorIndex < NUMBER_OF_SENSORS; sensorIndex++)
	{
		sensorStatus[sensorIndex].previousDistance = sensorStatus[sensorIndex].currentDistance;
		if (distanceSum != EMPTY)
		{
			sensorStatus[sensorIndex].currentDistance = (double)distanceSum / (double)averageCount;
		}
		else
		{
			sensorStatus[sensorIndex].currentDistance = EMPTY;
		}
	}

	// See if the amount of HIGHs exceed the Majority_threshould. If so, set it to true. 
	for (sensorIndex = 0; sensorIndex < NUMBER_OF_SENSORS; sensorIndex++)
	{
		sensorStatus[sensorIndex].previousHighLow = sensorStatus[sensorIndex].currentHighLow;
		if (sum[sensorIndex] >= ((double)READ_BUFFER_SIZE * MAJORITY_THRESHOULD))
		{
			sensorStatus[sensorIndex].currentHighLow = HIGH;
		}
		else
		{
			sensorStatus[sensorIndex].currentHighLow = LOW;
		}
	}

	// Prepare the buffer for read restart
	bufferIndex = 0; 
	readyToIdentify = true; 
}

void GestureTracker::ParseReading(char * sensorsInputStr)
{

	if (NUMBER_OF_SENSORS > 2)
	{
		printf("Error: ParseReading(str) must be updated.\n");
		while (1);
	}

	char * pChr = sensorsInputStr;

	pChr = strchr(sensorsInputStr, 'A');
	if (pChr != NULL)
	{
		*pChr = '\0';
	}
	pChr++;
	int sensorsInput[NUMBER_OF_SENSORS] = { 0 };
	if (sscanf(sensorsInputStr, "%d", &sensorsInput[LEFT_SENSOR]) == 0)
	{
		printf("Error: The string is invalid\n");
		while (1);
	}

	if (sscanf(pChr, "%d", &sensorsInput[RIGHT_SENSOR]) == 0)
	{
		printf("Error: The string is invalid\n");
		while (1);
	}

	ParseReading(sensorsInput);

}

void GestureTracker::ParseReading(int sensorsInput[])
{
	int sensorIndex = 0;
	for (sensorIndex = 0; sensorIndex < NUMBER_OF_SENSORS; sensorIndex++)
	{


		int readingHighLow = EMPTY;
		if ((sensorsInput[sensorIndex] >= MINIMUM_DISTANCE_FOR_HIGH) &&
			(sensorsInput[sensorIndex] <= MAXIMUM_DISTANCE_FOR_HIGH))
		{
			buffer_Distance[sensorIndex][bufferIndex] = sensorsInput[sensorIndex];
			readingHighLow = HIGH;
		}
		else
		{
			buffer_Distance[sensorIndex][bufferIndex] = EMPTY;
			readingHighLow = LOW;
		}
		buffer_HighLow[sensorIndex][bufferIndex] = readingHighLow;
	}
	bufferIndex++;


	if (bufferIndex >= READ_BUFFER_SIZE)
	{ // Buffer is Full.  
		ProcessBuffer();
	}
}

int GestureTracker::IdentifyGesture()
{

	if (readyToIdentify)
	{
		Sleep(500);
		double groupPreviousDistance = fmax(sensorStatus[LEFT_SENSOR].previousDistance, sensorStatus[RIGHT_SENSOR].previousDistance);
		double groupCurrentDistance = fmax(sensorStatus[LEFT_SENSOR].currentDistance, sensorStatus[RIGHT_SENSOR].currentDistance);

		if (((int)groupPreviousDistance != EMPTY) && ((int)groupCurrentDistance != EMPTY))
		{
			if (fabs(groupCurrentDistance - groupPreviousDistance) >= DISTANCE_DELTA)
			{
				if (groupCurrentDistance > groupPreviousDistance)
				{
					printf("\nSample Processed: Recognized <Pull action>!\n");
				}
				else
				{
					printf("\nSample Processed: Recognized <Push action>!\n");
				}
				readyToIdentify = false;
				Sleep(1000);
				return 0;
			}
		}
		

		if (
			(sensorStatus[LEFT_SENSOR].previousHighLow == LOW) &&
			(sensorStatus[LEFT_SENSOR].currentHighLow == HIGH) &&
			(sensorStatus[RIGHT_SENSOR].previousHighLow == HIGH) &&
			(sensorStatus[RIGHT_SENSOR].currentHighLow == LOW))
		{
			printf("\nSample Processed: Recognized <Swiped Left>!\n");
			readyToIdentify = false;
			Sleep(1000);
			return 0;
		}


		if (
			(sensorStatus[LEFT_SENSOR].previousHighLow == HIGH) &&
			(sensorStatus[LEFT_SENSOR].currentHighLow == LOW) &&
			(sensorStatus[RIGHT_SENSOR].previousHighLow == LOW) &&
			(sensorStatus[RIGHT_SENSOR].currentHighLow == HIGH))
		{
			printf("\nSample Processed: Recognized <Swiped Right>!\n");
			readyToIdentify = false;
			Sleep(1000);
			return 0;
		}

		printf("\nSample Processed: But no relevant pattern was identified. \n");

		readyToIdentify = false;
	}

	return 0;

}

#pragma once


typedef struct sensorNode
{
	int firstSensor;
	int secondSensor;
	struct sensorNode *next;
}sensorNode;


sensorNode insertNode(sensorNode *head, sensorNode *data);

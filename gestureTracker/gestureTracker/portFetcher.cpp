/*
*	FILE		  : portFetcher.cpp
*   PROJECT		  :	4X4
*   PROGRAMMER	  : Wesley Martin
*	FIRST VERSION : 3/2017
*/

#include "GestureTracker.h"


#using <System.dll>


#include <stdio.h>

/* #include <string>
#include <msclr\marshal_cppstd.h> */

using namespace System;
using namespace System::IO::Ports;



int main()
{
	SerialPort^ mySerialPort = gcnew SerialPort("COM5");

	mySerialPort->BaudRate = 9600;
	mySerialPort->Parity = Parity::None;
	mySerialPort->StopBits = StopBits::One;
	mySerialPort->DataBits = 8;
	mySerialPort->Handshake = Handshake::None;
	mySerialPort->RtsEnable = true;

	mySerialPort->Open();

	//Console::WriteLine("Press any key to continue...");
	//Console::WriteLine();
	//Console::ReadKey();
	GestureTracker gesture;
	int inputNumber = 1;
	while (1)
	{
		
		String^ sensor1 = mySerialPort->ReadTo("A");
		String^ sensor2 = mySerialPort->ReadTo("B");

		char sensorsInputStr[500] = "";
		sprintf(sensorsInputStr, "%sA%sB", sensor1, sensor2);
		//sprintf(sensorsInputStr, "%sA%sB", sensor1_str.c_str, sensor2_str.c_str);
		printf("%s", sensorsInputStr);  //, inputNumber,READ_BUFFER_SIZE,sensorsInputStr);
		gesture.ParseReading(sensorsInputStr);
		gesture.IdentifyGesture();

		inputNumber++;
		if (inputNumber >= READ_BUFFER_SIZE)
		{
			inputNumber = 1;
		}
	}

	mySerialPort->Close();

}
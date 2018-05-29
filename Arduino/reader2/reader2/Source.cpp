#using <System.dll>

#include <exception>
#include <stdio.h>
#include <iostream>
#include <string>
#include <regex>
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::IO::Ports;
using namespace System::IO;
using namespace System::ComponentModel;
using namespace msclr::interop;
void MouseMove(int x, int y);

int main()
{
	while(1)
	{
	array<String^>^ serialPorts = nullptr;
	try
	{
		// Get a list of serial port names.
		serialPorts = SerialPort::GetPortNames();
	}
	catch (Win32Exception^ ex)
	{
		Console::WriteLine(ex->Message);
	}

	Console::WriteLine("The following serial ports were found:");
	for each(String^ port in serialPorts)
	{
		Console::WriteLine(port);
	}
	SerialPort^ mySerialPort = nullptr;
	// Display each port name to the console.
	for each(String^ port in serialPorts)
	{
		mySerialPort = gcnew SerialPort(port);

		mySerialPort->BaudRate = 9600;
		mySerialPort->Parity = Parity::None;
		mySerialPort->StopBits = StopBits::One;
		mySerialPort->DataBits = 8;
		mySerialPort->Handshake = Handshake::None;
		mySerialPort->RtsEnable = true;

		while (!mySerialPort->IsOpen)
		{
			try {
				mySerialPort->Open();
			}
			catch (UnauthorizedAccessException^ e)
			{
				Console::WriteLine(e->Message);
				mySerialPort->Close();
			}
			catch (ArgumentOutOfRangeException^ e)
			{
				Console::WriteLine(e->Message);
				mySerialPort->Close();
			}
			catch (IOException^ e)
			{
				Console::WriteLine(e->Message);
				mySerialPort->Close();
			}
			catch (ArgumentException^ e)
			{
				Console::WriteLine(e->Message);
				mySerialPort->Close();
			}
			catch (InvalidOperationException^ e)
			{
				Console::WriteLine(e->Message);
				mySerialPort->Close();
			}
			
		}


		String^ testRead = mySerialPort->ReadTo("B");
		std::string test = msclr::interop::marshal_as<std::string>(testRead);
		if (std::regex_match(test, std::regex("[0-9]{3}A[0-9]{3}B")))
		{
			printf("Matching string");
			break;
		}

	}


	//Console::WriteLine("Press any key to continue...");
	//Console::WriteLine();
	//Console::ReadKey();

	while (1)
	{
		String^ test = nullptr;
		String^ test2 = nullptr;
		try
		{
			test = mySerialPort->ReadTo("A");
		}
		catch (IOException^ e)
		{
			break;
		}

		try
		{
			test2 = mySerialPort->ReadTo("B");
		}
		catch (IOException^ e)
		{
			break;
		}
		printf("First thing is: %s, Second thing is: %s\n", test, test2);
		std::string testng = msclr::interop::marshal_as<std::string>(test);
		int testInt = atoi(testng.c_str());
		if (testInt > 250)
		{
			MouseMove(100, 100);
		}
	}

	mySerialPort->Close();
}
}


void MouseMove(int x, int y)
{
	double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;
	double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;
	double fx = x*(65535.0f / fScreenWidth);
	double fy = y*(65535.0f / fScreenHeight);
	INPUT  Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	Input.mi.dx = fx;
	Input.mi.dy = fy;
	::SendInput(1, &Input, sizeof(INPUT));
}
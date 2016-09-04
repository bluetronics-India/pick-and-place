/*
* File: serial.cpp
* Author: Justin Wolf
* Date: 24/08/2016
* 
* Description: Implementation file for header file "serial.h"
*/

// include header file
#include "serial.h"

// create a variable in which to store the port
 SerialPort^ createPort() {
	 int baudRate = 9600;
	 SerialPort^ port = gcnew SerialPort("COM4", baudRate);
	 return port;
 }

// instantiates and opens a serial port
bool openPort(SerialPort^ port) {
	
	System::Console::WriteLine("Opening port");
	

	while(!port->IsOpen) {
		port->Open();
	}
	return true;
}

// closes the port
bool closePort(SerialPort^ port) {
	while (port->IsOpen) {
		port->Close();
	}
	return true;
}

// writes the argument passed to the port
void writeToPort(int msg) {
	SerialPort^ port = createPort();
	openPort(port);
	array<unsigned char>^ charArray = gcnew array<unsigned char>(1); 
	// Set number to send to the port
	charArray[0] = msg;
	// Write number to the port
	port->Write(charArray, 0, 1);
	closePort(port);
}
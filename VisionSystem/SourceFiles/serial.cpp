/*
* File: serial.cpp
* Author: Justin Wolf
* Date: 24/08/2016
* 
* Description: Allows interfacing through serial port communication.
*/


/*
******************************************* Include Declarations ******************************************
*/

#include "serial.h"

/*
****************************************** Variable Declarations ******************************************
*/


/*
****************************************** Method Implementations ******************************************
*/

/*
* Function: createPort
* Parameters: N/A
* Return: SerialPort^
* Purpose: create a variable in which to store the port
*/
 SerialPort^ createPort() {
	 int baudRate = 9600;
	 SerialPort^ port = gcnew SerialPort("COM4", baudRate);
	 return port;
 }

 /*
* Function: openPort
* Parameters: SerialPort^
* Return: boolean
* Purpose: instantiates and opens a serial port
*/
bool openPort(SerialPort^ port) {
	while(!port->IsOpen) {
		port->Open();
	}
	//std::cout << "Port opened" << std::endl;
	return true;
}

/*
* Function: closePort
* Parameters: SerialPort^
* Return: boolean
* Purpose: closes the port
*/
bool closePort(SerialPort^ port) {
	while (port->IsOpen) {
		port->Close();
	}
	return true;
}

/*
* Function: writeToPort
* Parameters: int
* Return: void
* Purpose: writes the argument passed to the port
*/
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
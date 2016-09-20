/*
* File: serial.h
* Author: Justin Wolf
* Date: 24/08/2016
* 
* Description: Allows interfacing through serial port communication.
*/

#ifndef SERIAL_H
#define SERIAL_H

/*
******************************************* Include Declarations ******************************************
*/

#using <system.dll>
#include <iostream>
using namespace System;
using namespace System::IO::Ports;

/*
******************************************* Method Declarations *******************************************
*/

bool openPort();
bool closePort();
void writeToPort(int);

#endif
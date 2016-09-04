/*
* File: serial.h
* Author: Justin Wolf
* Date: 24/08/2016
* 
* Description: Header for all source code dealing with writing to the serial port"
*/


#ifndef SERIAL_H
#define SERIAL_H

#using <system.dll>

using namespace System;
using namespace System::IO::Ports;

bool openPort();
bool closePort();
void writeToPort(int);

#endif
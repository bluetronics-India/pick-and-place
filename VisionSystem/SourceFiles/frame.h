/*
* File: 
* Author: Justin Wolf
* Date: 
* 
* Description: Allows the modification and manipulation of the opencv Mat object.
*/

#ifndef FRAME_H
#define FRAME_H

/*
******************************************* Include Declarations ******************************************
*/

#include <iostream>
#include <string>
#include "opencv2/highgui/highgui.hpp"

/*
******************************************* Method Declarations *******************************************
*/

cv::VideoCapture startCameraStream(int);
void createDisplay(std::string);
void displayFrame(std::string, cv::Mat);
void saveFrame(cv::Mat);
cv::Mat openImage(char*);

#endif
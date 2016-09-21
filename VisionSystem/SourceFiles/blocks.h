/*
* File: blocks.h
* Author: Justin Wolf
* Date: 
* 
* Description: Uses opencv features to detect different color blocks.
*/

#ifndef BLOCKS_H
#define BLOCKS_H

/*
******************************************* Include Declarations ******************************************
*/

#include <iostream>

#include "opencv2/opencv.hpp"
#include "contours.h"
#include "serial.h"

/*
******************************************* Method Declarations *******************************************
*/
bool intialisePos1(cv::Mat);
void setArea(cv::Mat);

void checkForColoredBlocks(cv::Mat);
bool checkRedBlockExists(cv::Mat);
bool checkBlueBlockExists(cv::Mat);
bool checkGreenBlockExists(cv::Mat);

cv::vector<cv::vector<cv::Point>> getRedContours(cv::Mat);
cv::vector<cv::vector<cv::Point>> getBlueContours(cv::Mat);
cv::vector<cv::vector<cv::Point>> getGreenContours(cv::Mat);

int checkPos(int, int);
int checkColor(int);
void sendMessage(int, int);

#endif
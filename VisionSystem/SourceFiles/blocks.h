#ifndef BLOCKS_H
#define BLOCKS_H


#include <iostream>

#include "opencv2/opencv.hpp"
#include "visionprocessing.h"
#include "serial.h"


/*
* Function declarations need to be implemented in the implementation file
*/
void intialisePos1(cv::Mat);
void checkForColoredBlocks(cv::Mat);
void checkPos(int, int);

#endif
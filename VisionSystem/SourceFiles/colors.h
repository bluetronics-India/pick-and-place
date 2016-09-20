/*
* File: 
* Author: Justin Wolf
* Date: 
* 
* Description: Uses opencv's color detection and modification features to allow an image to be thresholded
*              by its color.
*/

#ifndef COLORS_H
#define COLORS_H

/*
******************************************* Include Declarations ******************************************
*/
#include <iostream>

#include "opencv2/opencv.hpp"
#include "frame.h"

/*
******************************************* Method Declarations *******************************************
*/
cv::Mat convertToHSV(cv::Mat);
cv::Mat convertToGREY(cv::Mat);
cv::Mat colorThresholding(cv::Mat, int);

cv::Mat modifyWithTrackBars(cv::Mat);
void createTrackBars();

#endif
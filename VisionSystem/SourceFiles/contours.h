/*
* File: 
* Author: Justin Wolf
* Date: 
* 
* Description: opencv contour features specialised for locating a contour in a color thresholded image.
*/

#ifndef CONTOURS_H
#define CONTOURS_H

/*
******************************************* Include Declarations ******************************************
*/

#include <iostream>
#include "opencv2/opencv.hpp"
#include "colors.h"

/*
******************************************* Method Declarations *******************************************
*/

cv::vector<cv::vector<cv::Point>> getImageContours(cv::Mat);
int getContourIndex(cv::vector<cv::vector<cv::Point>>, double, double);
cv::Mat drawContours(cv::Mat, cv::vector<cv::vector<cv::Point>>, int);

double getContourArea(cv::vector<cv::Point>);

int getContourStartPointX(cv::vector<cv::Point>);
int getContourStartPointY(cv::vector<cv::Point>);

#endif
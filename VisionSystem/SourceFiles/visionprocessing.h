#ifndef VISIONPROCESSING_H
#define VISIONPROCESSING_H

#include <iostream>

#include "opencv2/opencv.hpp"
#include "vision.h"

/*
* Function declarations need to be implemented in the implementation file
*/
cv::Mat convertToHSV(cv::Mat);
cv::Mat convertToGREY(cv::Mat);
cv::Mat colorThresholding(cv::Mat, int);

cv::vector<cv::vector<cv::Point>> getImageContours(cv::Mat);
int getContourIndex(cv::vector<cv::vector<cv::Point>>);
cv::Mat drawContours(cv::Mat, cv::vector<cv::vector<cv::Point>>, int);

int getContourStartPointX(cv::vector<cv::Point>);
int getContourStartPointY(cv::vector<cv::Point>);

bool redContourExists(cv::Mat);
bool blueContourExists(cv::Mat);
bool greenContourExists(cv::Mat);

cv::vector<cv::Point> getRedContour(cv::Mat);
cv::vector<cv::Point> getBlueContour(cv::Mat);
cv::vector<cv::Point> getGreenContour(cv::Mat);

#endif
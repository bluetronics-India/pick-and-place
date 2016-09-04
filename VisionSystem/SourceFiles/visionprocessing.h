#ifndef VISIONPROCESSING_H
#define VISIONPROCESSING_H

//#include "opencv2/highgui/highgui.hpp"
//#include <vector>
#include <iostream>

#include "opencv2/opencv.hpp"


/*
* Function declarations need to be implemented in the implementation file
*/
cv::Mat convertToHSV(cv::Mat);
cv::Mat colorThresholding(cv::Mat, int);
void findRectangle(cv::Mat);

#endif
#ifndef VISION_H
#define VISION_H

#include <iostream>
#include <string>
#include <cstdlib> // allows access to environment variables
#include "opencv2/highgui/highgui.hpp"

cv::VideoCapture startCameraStream(int);
void createDisplay(std::string);
void displayFrame(std::string, cv::Mat);
void saveFrame(cv::Mat);
cv::Mat openImage(char*);

#endif
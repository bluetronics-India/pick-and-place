#include "visionprocessing.h"

#define RED 0
#define YELLOW 1
#define WHITE 2
#define BLUE 3

/*
* Vec3b[2] -> red
* Vec3b[1] -> green
* Vec3b[0] -> blue
*/

cv::Mat convertToHSV(cv::Mat frame) {
	cv::Mat hsv_image;
	cv::cvtColor(frame, hsv_image, CV_BGR2HSV);
	return hsv_image;
}

cv::Mat colorThresholding(cv::Mat hsv_image, int threshold_color) {
	
	cv::Mat threshold_image;

	switch (threshold_color) {
	case RED:
		inRange(hsv_image, cv::Scalar(136, 100, 75), cv::Scalar(179, 255, 255), threshold_image);
		break;
	case YELLOW:
		inRange(hsv_image, cv::Scalar(17, 70, 130), cv::Scalar(30, 160, 190), threshold_image);
		break;
	case WHITE:
		inRange(hsv_image, cv::Scalar(11, 12, 142), cv::Scalar(40, 80, 170), threshold_image);
		break;
	case BLUE:
		inRange(hsv_image, cv::Scalar(100, 85, 60), cv::Scalar(125, 140, 80), threshold_image);
		break;
	}
	return threshold_image;
}

void findRectangle(cv::Mat hsv_image) {
	cv::vector<cv::vector<cv::Point>> contours;
	cv::findContours(hsv_image, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	for(int i= 0; i < contours.size(); i++) {
		for(int j= 0; j < contours[i].size();j++) {
			std::cout << contours[i][j] << std::endl; //do whatever
			hsv_image.at<cv::Vec3b>(i,j)[0] = 255;
			hsv_image.at<cv::Vec3b>(i,j)[1] = 0;
			hsv_image.at<cv::Vec3b>(i,j)[2] = 0;
		}
	}
	
	//cv::drawContours(hsv_image, contours, -1, (0,255,0), 3);
}
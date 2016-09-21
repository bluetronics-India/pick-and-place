/*
* File: contours.cpp
* Author: Justin Wolf
* Date: 
* 
* Description: opencv contour features specialised for locating a contour in a color thresholded image.
*/

/*
******************************************* Include Declarations ******************************************
*/

#include "contours.h"

/*
****************************************** Constants Declarations ******************************************
*/

#define RED 0
#define YELLOW 1
#define WHITE 2
#define BLUE 3
#define GREEN 4
#define ALL 5

/*
****************************************** Variable Declarations ******************************************
*/

cv::vector<cv::Vec4i> hierarchy;
int minArea = 0;
int maxArea = 310000;

/*
****************************************** Method Implementations ******************************************
*/

/*
* Function: getImageContours
* Parameters: cv::Mat
* Return: cv::vector<cv::vector<cv::Point>>
* Purpose: Returns all contours found within a binary image
*/
cv::vector<cv::vector<cv::Point>> getImageContours(cv::Mat image) {
	cv::vector<cv::vector<cv::Point>> contours;
	cv::findContours(image, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);	
	return contours;
}

/*
* Function: drawContour
* Parameters: cv::Mat, cv::vector<cv::vector<cv::Point>>, int
* Return:
* Purpose: Draw the contour at the index onto the image
*/
cv::Mat drawContour(cv::Mat source_image, cv::vector<cv::vector<cv::Point>> contours, int index) {
	cv::drawContours(source_image, contours, index, CV_RGB(250,255,0), 2, 6, hierarchy);
	return source_image;
}

/*
* Function: drawContours
* Parameters: cv::Mat, cv::vector<cv::vector<cv::Point>>, int
* Return:
* Purpose: Draw all contours
*/
cv::Mat drawContours(cv::Mat source_image, cv::vector<cv::vector<cv::Point>> contours) {
	cv::drawContours(source_image, contours, -1, CV_RGB(250,255,0), 2, 6, hierarchy);
	return source_image;
}

/*
* Function: getContourArea
* Parameters: cv::vector<cv::vector<cv::Point>>, int
* Return:
* Purpose: Finds the area of a contour
*/
double getContourArea(cv::vector<cv::Point> contour) {
	return cv::contourArea(contour, false);
}

/*
* Function: getContourByArea
* Parameters: cv::vector<cv::vector<cv::Point>>
* Return: int
* Purpose: Finds the index of the contour which satusfues the area restriction
*/
int getContourByArea(cv::vector<cv::vector<cv::Point>> contours, double minArea, double maxArea) {
	if (contours.size() > 0) {
		//std::cout << "Total number of contours: " << contours.size() << std::endl;
		for (int i = 0; i < contours.size(); i++) {
			double area = cv::contourArea(contours[i], false);
			//std::cout << "Area of contour " << i << ": " << area << std::endl;
			if (area >= minArea && area <= maxArea) {
				//std::cout << contours[i] << std::endl;
				return i;
			}
		}
	}
	return -1;
}

/*
* Function: getContourByArea
* Parameters: cv::vector<cv::vector<cv::Point>>
* Return: int
* Purpose: Finds the index of the contour which satusfues the area restriction
*/
int getContourByArea(cv::vector<cv::vector<cv::Point>> contours) {
	if (contours.size() > 0) {
		//std::cout << "Total number of contours: " << contours.size() << std::endl;
		for (int i = 0; i < contours.size(); i++) {
			double area = cv::contourArea(contours[i], false);
			//std::cout << "Area of contour " << i << ": " << area << std::endl;
			if (area >= minArea && area <= maxArea) {
				//std::cout << contours[i] << std::endl;
				return i;
			}
		}
	}
	return -1;
}

/*
* Function: getContourStartPointX
* Parameters: cv::vector<cv::Point>
* Return: int
* Purpose: Returns the x coordinate of the first point of the contour
*/
int getContourStartPointX(cv::vector<cv::Point> contour) {
	return (int)contour[0].x;
}

/*
* Function: getContourStartPointY
* Parameters: cv::vector<cv::Point>
* Return: int
* Purpose: Returns the y coordinate of the first point of the contour
*/
int getContourStartPointY(cv::vector<cv::Point> contour) {
	return (int)contour[0].y;
}

/*
* Function: createAreaTrackBar
* Parameters: N/A
* Return: void
* Purpose: Create the trackbar to allow manual analysis fo the contour areas
*/
void createAreaTrackBars() {

	cv::namedWindow("Area Thresholds", CV_WINDOW_AUTOSIZE);
	
	//Create trackbars in "Control" window
	cvCreateTrackbar("minArea", "Area Thresholds", &minArea, 5000);
	cvCreateTrackbar("maxArea", "Area Thresholds", &maxArea, 5000);
}



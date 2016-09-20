/*
* File: frame.cpp
* Author: Justin Wolf
* Date: 
* 
* Description: Allows the modification and manipulation of the opencv Mat object.
*/

/*
******************************************* Include Declarations ******************************************
*/

#include "frame.h"

/*
****************************************** Variable Declarations ******************************************
*/

int imageCount = 0;

/*
****************************************** Method Implementations ******************************************
*/

 /*
* Function: startCameraStream
* Parameters: int
* Return: cv::VideoCapture
* Purpose: Open a stream to a camera and return it
*/
cv::VideoCapture startCameraStream(int camera) {
	cv::VideoCapture capture(camera);
	if (!capture.isOpened()) {
		std::cout<<"Couldnt open the camera"<<std::endl;
		exit(EXIT_FAILURE);
	}
	return capture;
}

 /*
* Function: createDisplay
* Parameters: std::string
* Return: void
* Purpose: create a display window
*/
void createDisplay(std::string windowName) {
	cv::namedWindow(windowName, CV_WINDOW_KEEPRATIO);
}

 /*
* Function: displayFrame
* Parameters: std::string, cv::Mat
* Return: void
* Purpose: display the frame in a named window whose name is the string parameter if it exists
*/
void displayFrame(std::string windowName, cv::Mat frame) {
	if (!frame.empty()) {
		cv::imshow(windowName, frame);
	}
}

 /*
* Function: saveFrame
* Parameters: cv::Mat
* Return: void
* Purpose: save a video frame as a png image
*/
void saveFrame(cv::Mat frame) {
	std::stringstream ss;
	ss << imageCount++;

	std::string filename = "capture.png";
	//	+  ss.str()
	//	+ ".png";
	cv::imwrite(filename,frame);
}

 /*
* Function: openImage
* Parameters: char*
* Return: cv::Mat
* Purpose: Open an image
*          Return image if successful
*/
cv::Mat openImage(char* fileName) {
	cv::Mat image = cv::imread(fileName, CV_LOAD_IMAGE_COLOR);
	if (!image.data) {
		std::cout << fileName << " failed to open" << std::endl;
		exit(EXIT_FAILURE);
	} else {
		std::cout << fileName << " opened successfully" << std::endl;
		return image;
	}
}

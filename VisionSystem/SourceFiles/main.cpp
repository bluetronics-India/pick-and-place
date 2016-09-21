/*
* File: main.cpp
* Author: Justin Wolf
* Date: 
* 
* Description: main file for the vision processing of the hand eye coordination project. 
*/

/*
******************************************* Include Declarations ******************************************
*/

#include "opencv2/highgui/highgui.hpp"
#include "frame.h"
#include "contours.h"
#include "blocks.h"
#include "serial.h"
#include <cstdlib>

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



/*
******************************************* Method Declarations *******************************************
*/

void processVideo(cv::VideoCapture);
void autoFiltering(cv::Mat);
void manualFiltering(cv::Mat);

/*
****************************************** Method Implementations ******************************************
*/

/*
* Function: main
* Parameters: int, char**
* Return: int
* Purpose: main program
*/
int main(int argc, char** argv) {
		// select what is to be processed
	if (argc < 2) {
		std::cout << "Please specify whether to process video or an image using -vid, -img, -test, or -ser after \"VisionSystem.exe\"" << std::endl;
		return 0;
	}
	//std::cout << "Argument: " << argv[1] << std::endl;
	if (std::strcmp(argv[1], "-vid") == 0) {
		if (argc != 3) {
			std::cout << "Incorrect program call please use \"VisionSystem.exe -vid 0\" for video stream processing" << std::endl;
			return 0;
		} else {
			// need to convert argv[2] to int
			cv::VideoCapture capture = startCameraStream(0);
			processVideo(capture);
		}
	} else if (std::strcmp(argv[1], "-img") == 0) {
		cv::Mat frame;
		if (argc > 2) {
			char* filename = argv[2];
			frame = openImage(filename);
			autoFiltering(frame);
		} else {
			cv::VideoCapture capture = startCameraStream(0);
			while((char)cv::waitKey(5) != 27){
				capture >> frame;
				autoFiltering(frame);
			}
		}
	} else if (std::strcmp(argv[1], "-test") == 0) {
		cv::Mat frame;
		if (argc > 2) {
			char* filename = argv[2];
			frame = openImage(filename);
			manualFiltering(frame);
		} else {
			createColorTrackBars();
			createAreaTrackBars();
			cv::VideoCapture capture = startCameraStream(0);

			while((char)cv::waitKey(5) != 27){
				capture >> frame;
				manualFiltering(frame);
			}
		}
	} else if (std::strcmp(argv[1], "-ser") == 0) {
		if (argc != 3) {
			std::cout << "Incorrect program call please use \"VisionSystem.exe -ser\" followed by the number to write to the serial port." << std::endl;
			return 0;
		} else {
			std::cout << "Writing " << argv[2] << " to parallel port." << std::endl;
			writeToPort(atoi(argv[2]));
		}
	} else {
		std::cout << "You are an IDIOT!!!!" << std::endl;
		return 0;
	}
	return 1;
}

/*
* Function: processVideo
* Parameters: cv::VideoCapture
* Return: void
* Purpose: Process a camera input for colored blocks
*/
void processVideo(cv::VideoCapture capture) {
	cv::Mat frame;
	std::cout << "Please place red block in position 1." << std::endl;
	std::cin.ignore(); // wait for key press
	// allow camera to adjust to background and lighting
	for (int i = 0; i < 10; i++) {
		capture >> frame;
	}
	//displayFrame("Initial View", frame);
	cv::waitKey(5);
	while (!intialisePos1(frame)) {
		capture >> frame;
		intialisePos1(frame);
	}

	std::cin.ignore(); // wait for key press
	
	while ((char)cv::waitKey(5) != 27) {
		capture >> frame;
		checkForColoredBlocks(frame);
		displayFrame("Current Image", frame);
		saveFrame(frame);
	}
}

/*
* Function: autoFiltering
* Parameters: cv::Mat
* Return: void
* Purpose:
*/
void autoFiltering(cv::Mat frame) {
	cv::Mat red_image, blue_image, green_image;
	red_image = colorThresholding(frame, RED);
	blue_image = colorThresholding(frame, BLUE);
	green_image = colorThresholding(frame, GREEN);

	displayFrame("Red Thresholded", red_image);
	cv::waitKey(5);
	displayFrame("Blue Thresholded", blue_image);
	cv::waitKey(5);
	displayFrame("Green Thresholded", green_image);
	cv::waitKey(5);
}

/*
* Function: manualFiltering
* Parameters: cv::Mat
* Return: void
* Purpose: Allow manual color thresholding 
*/
void manualFiltering(cv::Mat frame) {
	cv::Mat thresholded_image, contoured_image, area_image;
	
	displayFrame("Original Image", frame);
	thresholded_image = manualColorFiltering(frame);
	displayFrame("Colors", thresholded_image);
	cv::vector<cv::vector<cv::Point>> contours = getImageContours(thresholded_image);
	contoured_image = drawContours(frame.clone(), contours);
	displayFrame("Contours", contoured_image);
	int index = getContourByArea(contours);
	std::cout << "Index: " << index << std::endl;
	if (index != -1) {
		std::cout << "Area: " << getContourArea(contours[index]);
		area_image = drawContour(frame.clone(), contours, index);
		displayFrame("Contour By Area", area_image);
	}
}
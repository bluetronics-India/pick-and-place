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
void processImage(cv::Mat);
void testProcessImage(cv::Mat);

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
		std::cout << "Please specify whether to process video or an image using -vid or -img after \"VisionSystem.exe\"" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (std::strcmp(argv[1], "-vid") == 0) {
		if (argc != 3) {
			std::cout << "Incorrect program call please use \"VisionSystem.exe -vid 0\" for video stream processing" << std::endl;
			exit(EXIT_FAILURE);;
		} else {
			// need to convert argv[2] to int
			cv::VideoCapture capture = startCameraStream(0);
			processVideo(capture);
		}
	} else if (std::strcmp(argv[1], "-img") == 0) {
		if (argc != 3) {
			std::cout << "Incorrect program call please use \"VisionSystem.exe -img filename\" for image processing" << std::endl;
			exit(EXIT_FAILURE);
		} else {
			cv::Mat frame;
			cv::VideoCapture capture = startCameraStream(0);
			capture >> frame;
			processImage(frame);
			//std::cout << "it worked" << std::endl;
		}
	} else if (std::strcmp(argv[1], "-test") == 0) {
		cv::Mat frame;
		if (argc > 2) {
			char* filename = argv[2];
			frame = openImage(filename);
		} else {
			cv::VideoCapture capture = startCameraStream(0);
			cv::waitKey(5000);
			capture >> frame;
		}
		testProcessImage(frame);
	} else {
		std::cout << "You are an IDIOT!!!!" << std::endl;
		exit(EXIT_FAILURE);
	}
	return 0;
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
		displayFrame("Image", frame);
		saveFrame(frame);
	}
}

/*
* Function: processImage
* Parameters: cv::Mat
* Return: void
* Purpose:
*/
void processImage(cv::Mat frame) {
	intialisePos1(frame);

}

/*
* Function: testProcessImage
* Parameters: cv::Mat
* Return: void
* Purpose: Allow manual colr thresholding 
*/
void testProcessImage(cv::Mat frame) {
	cv::Mat thresholded_image, contoured_image;
	createTrackBars();
	
	while ((char)cv::waitKey(5) != 27) {
		displayFrame("Original Image", frame);
		thresholded_image = modifyWithTrackBars(frame);
		displayFrame("Colors", thresholded_image);
		cv::vector<cv::vector<cv::Point>> contours = getImageContours(thresholded_image);
		int index = getContourIndex(contours, 0, 10000);
		std::cout << "index: " << index << std::endl;
		//contoured_image = drawContours(frame.clone(), contours, index);
		displayFrame("Contours", contoured_image);
		std::cout << "Area: " << getContourArea(contours[index]);
	}
}
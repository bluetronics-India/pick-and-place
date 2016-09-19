#include "opencv2/highgui/highgui.hpp"
#include "vision.h"
#include "visionprocessing.h"
#include "blocks.h"

#define RED 0
#define YELLOW 1
#define WHITE 2
#define BLUE 3
#define GREEN 4
#define ALL 5

void processVideo(cv::VideoCapture);
void processImage(cv::Mat);
void testProcessImage(cv::Mat);

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
		//cv::VideoCapture capture = startCameraStream(0);
		//cv::Mat frame;
		cv::Mat source_image = openImage("images\\capture.png");
		//capture >> frame;
		testProcessImage(source_image);
	} else {
		std::cout << "You are an IDIOT!!!!" << std::endl;
		exit(EXIT_FAILURE);
	}
	return 0;
}

void processVideo(cv::VideoCapture capture) {
	cv::Mat frame;
	capture >> frame;
	//displayFrame("Initial View", frame);
	cv::waitKey(5);
	while (!intialisePos1(frame)) {
		capture >> frame;
		intialisePos1(frame);
	}
	
	while ((char)cv::waitKey(5) != 27) {
		capture >> frame;
		checkForColoredBlocks(frame);
		displayFrame("Image", frame);
		saveFrame(frame);
	}
}

void processImage(cv::Mat frame) {

	//intialisePos1(frame);

	if (blueContourExists(frame)) {
		std::cout << "found blue contour" << std::endl;
	} else {
		std::cout << "failed" << std::endl;
	}
	//blue_contour = getBlueContour(frame);
	// get contours corner
	//int blueX = getContourStartPointX(blue_contour);
	//int blueY = getContourStartPointY(blue_contour);
	//checkPos(blueX, blueY);

	//checkForColoredBlocks(source_image);
}

void testProcessImage(cv::Mat frame) {
	cv::Mat thresholded_image, contoured_image;
	createTrackBars();
	
	while ((char)cv::waitKey(5) != 27) {
		displayFrame("Original Image", frame);
		thresholded_image = modifyWithTrackBars(frame);
		displayFrame("Colors", thresholded_image);
		contoured_image = drawContours(frame.clone(), getImageContours(thresholded_image), getContourIndex(getImageContours(thresholded_image)));
		displayFrame("Contours", contoured_image);
	}
}
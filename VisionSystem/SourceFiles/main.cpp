#include "opencv2/highgui/highgui.hpp"
#include "vision.h"
#include "visionprocessing.h"

#define RED 0
#define YELLOW 1
#define WHITE 2
#define BLUE 3

void processVideo(cv::VideoCapture);
void processImage(char*);
void testProcessImage(char*);
void createTrackBars();
cv::Mat modifyWithTrackBars(cv::Mat);

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
			processImage(argv[2]);
			//std::cout << "it worked" << std::endl;
		}
	} else if (std::strcmp(argv[1], "-test") == 0) {
		testProcessImage("TestImages\\test.png");
	} else {
		std::cout << "You are an IDIOT!!!!" << std::endl;
		exit(EXIT_FAILURE);
	}
}

void processVideo(cv::VideoCapture capture) {
	int keyboard = 0;
	cv::Mat frame;
	createDisplay("VS Before Filters");
	while ((char)keyboard != 27) {
		capture >> frame;
		displayFrame("Before Filters", frame);
		keyboard = cv::waitKey(5);
	}
}

void processImage(char* filename) {
	cv::Mat image, background_image, threshold_image;

	image = openImage(filename);


	//threshold_image = colorThresholding(image, RED);
	//displayFrame("Color Threshold", threshold_image);

	//threshold_image = convertToGREY(threshold_image);
	//blur(threshold_image, threshold_image, cv::Size(3,3));
	//displayFrame("Grey Color", threshold_image);
	//threshold(threshold_image, threshold_image, 20, 255, CV_THRESH_BINARY);
	
	//threshold_image = findEdges(image, "GREY");
	//displayFrame("Threshold Grey", threshold_image);
	
	while ((char)cv::waitKey(0) != 27) {
		exit(EXIT_SUCCESS);
	}
}

void testProcessImage(char* filename) {
	cv::Mat source_image, thresholded_image, contoured_image;

	source_image = openImage(filename);
	//displayFrame("Original Image", source_image);
	
	createTrackBars();
	
	while ((char)cv::waitKey(5) != 27) {
		displayFrame("Original Image", source_image);
		thresholded_image = modifyWithTrackBars(source_image);
		displayFrame("Colors", thresholded_image);
		contoured_image = findEdges(source_image.clone(), thresholded_image, "HSV");
		displayFrame("Contours", contoured_image);
	}
	exit(EXIT_SUCCESS);
}
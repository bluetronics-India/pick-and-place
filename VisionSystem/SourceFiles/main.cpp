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

char* backgroundLocation = "TestImages\\background.jpg";
int iLowH = 0;
int iHighH = 179;
int iLowS = 0; 
int iHighS = 255;
int iLowV = 0;
int iHighV = 255;

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
	cv::Mat image, hsv_image, threshold_image;
	image = openImage(filename);
	hsv_image = convertToHSV(image);
	threshold_image = colorThresholding(hsv_image, RED);
	displayFrame("Color Threshold", threshold_image);

	findRectangle(threshold_image);
	displayFrame("Threshold Colors", threshold_image);
	while ((char)cv::waitKey(0) != 27) {
		exit(EXIT_SUCCESS);
	}
}

void testProcessImage(char* filename) {
	cv::Mat image, hsv_image, threshold_image;
	image = openImage(filename);
	hsv_image = convertToHSV(image);
	createTrackBars();
	displayFrame("Original Image", image);

	while ((char)cv::waitKey(5) != 27) {
		threshold_image = modifyWithTrackBars(hsv_image);
		displayFrame("Threshold Colors", threshold_image);
	}
	exit(EXIT_SUCCESS);
}

void createTrackBars() {
	cv::namedWindow("Control", CV_WINDOW_AUTOSIZE);
	
	//Create trackbars in "Control" window
	cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "Control", &iHighH, 179);
	cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Control", &iHighS, 255);
	cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);
}

cv::Mat modifyWithTrackBars(cv::Mat image) {
	cv::Mat imageThresholded;
	inRange(image, cv::Scalar(iLowH, iLowS, iLowV), cv::Scalar(iHighH, iHighS, iHighV), imageThresholded);
	return imageThresholded;
}
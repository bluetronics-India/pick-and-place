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

int iLowH = 0;
int iHighH = 179;
int iLowS = 0; 
int iHighS = 255;
int iLowV = 0;
int iHighV = 255;

// BGR to HSV converter
cv::Mat convertToHSV(cv::Mat image) {
	cv::Mat hsv_image;
	cv::cvtColor(image, hsv_image, CV_BGR2HSV);
	//std::cout << "Successfully converted BGR image to HSV image" << std::endl;
	return hsv_image;
}

// BGR to Greyscale converter
cv::Mat convertToGREY(cv::Mat image) {
	cv::Mat grey_image;
	cv::cvtColor(image, grey_image, CV_BGR2GRAY);
	//std::cout << "Successfully converted BGR image to Greyscale image" << std::endl;
	return grey_image;
}

cv::Mat colorThresholding(cv::Mat image, int threshold_color) {

	cv::Mat hsv_image, threshold_image;
	
	hsv_image = convertToHSV(image);
	
	switch (threshold_color) {
	case RED:
		inRange(hsv_image, cv::Scalar(45, 60, 100), cv::Scalar(179, 255, 255), threshold_image);
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

cv::Mat findEdges(cv::Mat source_image, cv::Mat image, std::string image_format) {
	cv::vector<cv::vector<cv::Point>> contours;
	cv::vector<cv::Vec4i> hierarchy;
	cv::Mat image_to_contour;
	int thresh = 180; // play with for this specific
	int largest_contour_area = 0;
	int largest_contour_index = 0;

	if (image_format == "HSV") {
		image_to_contour = image;
	} else if (image_format == "GREY") {
		image_to_contour = convertToGREY(image);
		threshold(image_to_contour, image_to_contour, thresh, 255, CV_THRESH_BINARY);
	} else {
		std::cout << "Image format not supported. Please use greayscale or HSV." << std::endl;
		exit(EXIT_FAILURE);
	}

	cv::findContours(image_to_contour, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	
	/*for(int i= 0; i < contours.size(); i++) {
		double area = cv::contourArea(contours[i], false);
		if (area > largest_contour_area) {
			largest_contour_area = area;
			largest_contour_index = i;
		}
	}*/
	if (contours.size() > 0) {
		cv::drawContours(source_image, contours, -1, CV_RGB(250,255,0), 2, 6, hierarchy);
	}
	return source_image;
}

// Create the trackbars to get the thresholds required
void createTrackBars() {

	cv::namedWindow("Control", CV_WINDOW_AUTOSIZE);
	
	//Create trackbars in "Control" window
	cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "Control", &iHighH, 179);
	cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Control", &iHighS, 255);
	cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);

	std::cout << "Trackbars interface successfully initialised." << std::endl;
}

// Converts image to HSV
// Thresholds image based on values obtained from the trackbars
// Returns thresholded binary image
cv::Mat modifyWithTrackBars(cv::Mat image) {
	cv::Mat hsv_image, imageThresholded;
	hsv_image = convertToHSV(image);
	inRange(hsv_image, cv::Scalar(iLowH, iLowS, iLowV), cv::Scalar(iHighH, iHighS, iHighV), imageThresholded);
	return imageThresholded;
}
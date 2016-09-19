#include "visionprocessing.h"

#define RED 0
#define YELLOW 1
#define WHITE 2
#define BLUE 3
#define GREEN 4
#define ALL 5

int iLowH = 0;
int iHighH = 179;
int iLowS = 0; 
int iHighS = 255;
int iLowV = 0;
int iHighV = 255;

cv::vector<cv::Vec4i> hierarchy;

bool redContourExists(cv::Mat image) {
	image = colorThresholding(image, RED);
	cv::vector<cv::vector<cv::Point>> contours = getImageContours(image);
	int red_contour_index = getContourIndex(contours);
	if (red_contour_index == -1) {
		return false;
	} else {
		return true;
	}
}

cv::vector<cv::Point> getRedContour(cv::Mat image) {
	image = colorThresholding(image, RED);
	cv::vector<cv::vector<cv::Point>> contours = getImageContours(image);
	int red_contour_index = getContourIndex(contours);
	return contours[red_contour_index];
}

bool blueContourExists(cv::Mat image) {
	image = colorThresholding(image, BLUE);
	//displayFrame("blue", image);
	//cv::waitKey(1000);
	cv::vector<cv::vector<cv::Point>> contours = getImageContours(image);
	int blue_contour_index = getContourIndex(contours);
	if (blue_contour_index == -1) {
		//std::cout << "index -1" << std::endl;
		return false;
	} else {
		return true;
	}
}

cv::vector<cv::Point> getBlueContour(cv::Mat image) {
	image = colorThresholding(image, BLUE);
	cv::vector<cv::vector<cv::Point>> contours = getImageContours(image);
	int blue_contour_index = getContourIndex(contours);
	return contours[blue_contour_index];
}

bool greenContourExists(cv::Mat image) {
	image = colorThresholding(image, GREEN);
	cv::vector<cv::vector<cv::Point>> contours = getImageContours(image);
	int green_contour_index = getContourIndex(contours);
	if (green_contour_index == -1) {
		return false;
	} else {
		return true;
	}
}

cv::vector<cv::Point> getGreenContour(cv::Mat image) {
	image = colorThresholding(image, GREEN);
	cv::vector<cv::vector<cv::Point>> contours = getImageContours(image);
	int green_contour_index = getContourIndex(contours);
	return contours[green_contour_index];
}

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

// Converts image from BGR to HSV and then creates a binary image based on color thresholds
cv::Mat colorThresholding(cv::Mat image, int threshold_color) {
	cv::Mat hsv_image, threshold_image, lower_red, upper_red;
	hsv_image = convertToHSV(image);
	
	switch (threshold_color) {
	case RED:
		inRange(hsv_image, cv::Scalar(0, 40, 140), cv::Scalar(20, 255, 255), lower_red);
		//displayFrame("lower red", lower_red);
		inRange(hsv_image, cv::Scalar(140, 40, 140), cv::Scalar(180, 255, 255), upper_red);
		//displayFrame("upper red", upper_red);
		addWeighted(lower_red, 1.0, upper_red, 1.0, 0.0, threshold_image);
		//displayFrame("combined", threshold_image);
		//cv::waitKey(10000);
		break;
	case YELLOW:
		inRange(hsv_image, cv::Scalar(17, 70, 130), cv::Scalar(30, 160, 190), threshold_image);
		break;
	case WHITE:
		inRange(hsv_image, cv::Scalar(11, 12, 142), cv::Scalar(40, 80, 170), threshold_image);
		break;
	case BLUE:
		inRange(hsv_image, cv::Scalar(75, 75, 75), cv::Scalar(120, 255, 255), threshold_image);
		break;
	case GREEN:
		inRange(hsv_image, cv::Scalar(50, 40, 40), cv::Scalar(100, 255, 200), threshold_image);
		break;
	case ALL:
		inRange(hsv_image, cv::Scalar(0, 0, 0), cv::Scalar(179, 255, 255), threshold_image);
		break;
	}
	return threshold_image;
}

cv::vector<cv::vector<cv::Point>> getImageContours(cv::Mat image) {
	cv::vector<cv::vector<cv::Point>> contours;
	cv::findContours(image, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);	
	return contours;
}

// Perform checks on contours passed as parameter
int getContourIndex(cv::vector<cv::vector<cv::Point>> contours) {
	if (contours.size() > 0) {
		//std::cout << "Total number of contours: " << contours.size() << std::endl;
		for (int i = 0; i < contours.size(); i++) {
			double area = cv::contourArea(contours[i], false);
			//std::cout << "Area of contour " << i << ": " << area << std::endl;
			if (area >= 700 && area <= 1200) {
				return i;
			}
		}
	}
	return -1;
}

int getContourStartPointX(cv::vector<cv::Point> contour) {
	return (int)contour[0].x;
}

int getContourStartPointY(cv::vector<cv::Point> contour) {
	return (int)contour[0].y;
}

// Draw contours onto image passed as parameter
cv::Mat drawContours(cv::Mat source_image, cv::vector<cv::vector<cv::Point>> contours, int index) {
	cv::drawContours(source_image, contours, index, CV_RGB(250,255,0), 2, 6, hierarchy);
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
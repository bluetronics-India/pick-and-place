/*
* File: blocks.cpp
* Author: Justin Wolf
* Date: 
* 
* Description: 
*/

/*
******************************************* Include Declarations ******************************************
*/

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

#define ERROR 25
#define POS1 1
#define POS2 2
#define POS3 4
#define REDBLOCK 8
#define BLUEBLOCK 16
#define GREENBLOCK 32
/*
****************************************** Variable Declarations ******************************************
*/

int pos1X;
int pos1Y;
double minArea;
double maxArea;

int redX;
int redY;
int blueX;
int blueY;
int greenX;
int greenY;

/*
****************************************** Method Implementations ******************************************
*/

/*
* Function: intialisePos1
* Parameters: cv::Mat
* Return: boolean
* Purpose: Initialise the x and y coords of pos1
*          Initialise area expected of contours
*/
bool intialisePos1(cv::Mat frame) {
	// find red block in pos 1
	cv::vector<cv::vector<cv::Point>> contours = getRedContours(frame);
	if (contours.size() < 1) {
		std::cout << "Red block not found in position 1" << std::endl;
		return false;
	} else {
		for (int i = 0; i < contours.size(); i++) {
			std::cout << "Contour " << i << " area:" << getContourArea(contours[i]) << std::endl;
		}
		double area;
		std::cout << "Please enter the area of the contour from the list above." << std::endl;
		std::cin >> area;
		minArea = area - 500;
		maxArea = area + 500;
		
		int index = getContourByArea(contours, minArea, maxArea);
		if (index == -1) {
			return false;
		} else {
			// set x and y
			pos1X = getContourStartPointX(contours[index]);
			pos1Y = getContourStartPointY(contours[index]);
		}
		std::cout << "Pos1X: " << pos1X << " Pos1Y: " << pos1Y << std::endl;
		return true;
	}
}

/*
* Function: checkForColoredBlocks
* Parameters: cv::Mat
* Return: void
* Purpose: Looks for a colored block
*          If found checks its position
*/
void checkForColoredBlocks(cv::Mat frame) {
	if (checkRedBlockExists(frame)) {
		sendMessage(checkPos(redX, redY), checkColor(RED));
	} else if (checkBlueBlockExists(frame)) {
		sendMessage(checkPos(blueX, blueY), checkColor(BLUE));
	} else if (checkGreenBlockExists(frame)) {
		sendMessage(checkPos(greenX, greenY), checkColor(GREEN));
	} else {
		// empty workspace do nothing
		std::cout << "no blocks found" << std::endl;
		writeToPort(0);
	}
}

/*
* Function: checkRedBlockExists
* Parameters: cv::Mat
* Return: bool
* Purpose: Looks for a red block
*          If found checks sets the red block x and y coordinates
*/
bool checkRedBlockExists(cv::Mat frame) {
	cv::vector<cv::vector<cv::Point>> contours = getRedContours(frame);
	if (contours.size() < 1) {
		return false;
	} else {
		int index = getContourByArea(contours, minArea, maxArea);
		if (index == -1) {
			return false;
		} else {
			// set x and y
			redX = getContourStartPointX(contours[index]);
			redY = getContourStartPointY(contours[index]);
			return true;
		}
	}
}

/*
* Function: checkBlueBlockExists
* Parameters: cv::Mat
* Return: bool
* Purpose: Looks for a blue block
*          If found checks sets the blue block x and y coordinates
*/
bool checkBlueBlockExists(cv::Mat frame) {
	cv::vector<cv::vector<cv::Point>> contours = getBlueContours(frame);
	if (contours.size() < 1) {
		return false;
	} else {
		int index = getContourByArea(contours, minArea, maxArea);
		if (index == -1) {
			return false;
		} else {
			// set x and y
			blueX = getContourStartPointX(contours[index]);
			blueY = getContourStartPointY(contours[index]);
			return true;
		}
	}
}

/*
* Function: checkGreenBlockExists
* Parameters: cv::Mat
* Return: void
* Purpose: Looks for a green block
*          If found checks sets the green block x and y coordinates
*/
bool checkGreenBlockExists(cv::Mat frame) {
	cv::vector<cv::vector<cv::Point>> contours = getGreenContours(frame);
	if (contours.size() < 1) {
		return false;
	} else {
		int index = getContourByArea(contours, minArea, maxArea);
		if (index == -1) {
			return false;
		} else {
			// set x and y
			greenX = getContourStartPointX(contours[index]);
			greenY = getContourStartPointY(contours[index]);
			return true;
		}
	}
}

/*
* Function: getRedContours
* Parameters: cv::Mat
* Return: cv::vector<cv::vector<cv::Point>>
* Purpose: Finds the contours in a binary image that was thresholded for red
*/
cv::vector<cv::vector<cv::Point>> getRedContours(cv::Mat image) {
	image = colorThresholding(image, RED);
	cv::vector<cv::vector<cv::Point>> contours = getImageContours(image);
	return contours;
}

/*
* Function: getBlueContours
* Parameters: cv::Mat
* Return: cv::vector<cv::vector<cv::Point>>
* Purpose: Finds the contours in a binary image that was thresholded for blue
*/
cv::vector<cv::vector<cv::Point>> getBlueContours(cv::Mat image) {
	image = colorThresholding(image, BLUE);
	cv::vector<cv::vector<cv::Point>> contours = getImageContours(image);
	return contours;
}

/*
* Function: getGreenContours
* Parameters: cv::Mat
* Return: cv::vector<cv::vector<cv::Point>>
* Purpose: Finds the contours in a binary image that was thresholded for green
*/
cv::vector<cv::vector<cv::Point>> getGreenContours(cv::Mat image) {
	image = colorThresholding(image, GREEN);
	cv::vector<cv::vector<cv::Point>> contours = getImageContours(image);
	return contours;
}

/*
* Function: checkPos
* Parameters: int, int
* Return: int
* Purpose: Compares x and y parameter values with position 1 x and y values
*          Finds the correct value to send through the serial port for the determined position
*/
int checkPos(int blockX, int blockY) {
	//std::cout << "pos1X: " << pos1X << " pos1Y: " << pos1Y << std::endl;
	//std::cout << "blockX: " << blockX << " blockY: " << blockY << std::endl;
	int lowerThreshX = pos1X - ERROR;
	int upperThreshX = pos1X + ERROR;
	int lowerThreshY = pos1Y - ERROR;
	int upperThreshY = pos1Y + ERROR;

	if ((blockX >= lowerThreshX && blockX <= upperThreshX) && (blockY >= lowerThreshY && blockY <= upperThreshY)) {
		// write position 1 output to serial port
		std::cout << "Go to position 1" << std::endl;
		return POS1;
	} else if (blockX < lowerThreshX && blockY < lowerThreshY) {
		// write position 2 output to serial port
		std::cout << "Go to position 2" << std::endl;
		return POS2;
	} else if (blockX > upperThreshX && blockY < lowerThreshY) {
		// write position 3 output to serial port
		std::cout << "Go to position 3" << std::endl;
		return POS3;
	} else {
		return 0;
	}
}

/*
* Function: checkColor
* Parameters: int
* Return: int
* Purpose: Finds the correct value to send through the serial port for the color block
*/
int checkColor(int color) {
	if (color == RED) {
		return REDBLOCK;
	} else if (color == BLUE) {
		return BLUEBLOCK;
	} else if (color == GREEN) {
		return GREENBLOCK;
	} else {
		return 0;
	}
}

/*
* Function: sendMessage
* Parameters: int, int
* Return: void
* Purpose: Combines the found message components to generate the correct serial port output.
*/
void sendMessage(int position, int color) {
	writeToPort(position + color);
}
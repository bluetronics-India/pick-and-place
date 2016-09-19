#include "blocks.h"

#define RED 0
#define YELLOW 1
#define WHITE 2
#define BLUE 3
#define GREEN 4
#define ALL 5

int pos1X;
int pos1Y;

bool intialisePos1(cv::Mat frame) {
	std::cout << "Please place red block in position 1." << std::endl;
	
	// find red block in pos 1
	if (!redContourExists(frame)) {
		std::cout << "Red block not found in position 1" << std::endl;
		return false;
	}
	cv::vector<cv::Point> red_contour = getRedContour(frame);
	// get contours corner
	pos1X = getContourStartPointX(red_contour);
	pos1Y = getContourStartPointY(red_contour);
	std::cout << "Pos1X: " << pos1X << " Pos1Y: " << pos1Y << std::endl;
	return true;
}

void checkForColoredBlocks(cv::Mat frame) {
	cv::vector<cv::Point> red_contour;
	cv::vector<cv::Point> blue_contour;
	cv::vector<cv::Point> green_contour;

	if (redContourExists(frame)) {
		std::cout << "Red block exists" << std::endl;
		red_contour = getRedContour(frame);
		// get contours corner
		int redX = getContourStartPointX(red_contour);
		int redY = getContourStartPointY(red_contour);
		checkPos(redX, redY);
	} else if (blueContourExists(frame)) {
		blue_contour = getBlueContour(frame);
		// get contours corner
		int blueX = getContourStartPointX(blue_contour);
		int blueY = getContourStartPointY(blue_contour);
		checkPos(blueX, blueY);
	} else if (greenContourExists(frame)) {
		green_contour = getGreenContour(frame);
		// get contours corner
		int greenX = getContourStartPointX(green_contour);
		int greenY = getContourStartPointY(green_contour);
		checkPos(greenX, greenY);
	}
}

void checkPos(int blockX, int blockY) {
	std::cout << "pos1X: " << pos1X << " pos1Y: " << pos1Y << std::endl;
	std::cout << "blockX: " << blockX << " blockY: " << blockY << std::endl;

	if ((blockX >= (pos1X - 10) && blockX <= (pos1X + 10)) && (blockY >= (pos1Y - 10) && blockY <= (pos1Y + 10))) {
		// write position 1 output to serial port
		writeToPort(1);
		std::cout << "Go to position 1" << std::endl;
	} else if (blockX <= (pos1X - 10)) {
		// write position 2 output to serial port
		writeToPort(2);
		std::cout << "Go to position 2" << std::endl;
	} else if (blockX >= (pos1X + 10)) {
		// write position 3 output to serial port
		writeToPort(4);
		std::cout << "Go to position 3" << std::endl;
	}
}
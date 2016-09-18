#include "blocks.h"

#define RED 0
#define YELLOW 1
#define WHITE 2
#define BLUE 3
#define GREEN 4
#define ALL 5

int pos1X;
int pos1Y;

void intialisePos1(cv::Mat frame) {
	std::cout << "Please place red block in position 1" << std::endl;
	
	// find red block in pos 1
	while (!redContourExists(frame)) {
		std::cout << "Red block not found in position 1" << std::endl;
	}
	cv::vector<cv::Point> red_contour = getRedContour(frame);
	// get contours corner
	pos1X = getContourStartPointX(red_contour);
	pos1Y = getContourStartPointY(red_contour);
}

void checkForColoredBlocks(cv::Mat frame) {
	while (1) {
		cv::vector<cv::Point> red_contour;
		cv::vector<cv::Point> blue_contour;
		cv::vector<cv::Point> green_contour;

		while (redContourExists(frame)) {
			red_contour = getRedContour(frame);
			// get contours corner
			int redX = getContourStartPointX(red_contour);
			int redY = getContourStartPointY(red_contour);
			checkPos(redX, redY);
		}
		while (blueContourExists(frame)) {
			blue_contour = getBlueContour(frame);
			// get contours corner
			int blueX = getContourStartPointX(blue_contour);
			int blueY = getContourStartPointY(blue_contour);
			checkPos(blueX, blueY);
		}
		while (greenContourExists(frame)) {
			green_contour = getGreenContour(frame);
			// get contours corner
			int greenX = getContourStartPointX(green_contour);
			int greenY = getContourStartPointY(green_contour);
			checkPos(greenX, greenY);
		}
	}
}

void checkPos(int blockX, int blockY) {
	if ((blockX >= (pos1X - 10) && blockX <= (pos1X + 10)) && (blockY >= (pos1Y - 10) && blockY <= (pos1Y + 10))) {
		// write position 1 output to serial port
		writeToPort(1);
	} else if (blockY <= (pos1Y - 10)) {
		// write position 2 output to serial port
		writeToPort(2);
	} else if (blockY >= (pos1Y + 10)) {
		// write position 3 output to serial port
		writeToPort(4);
	}
}
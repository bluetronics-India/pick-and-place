#include "vision.h"

int imageCount = 0;

// open a stream to a camera
cv::VideoCapture startCameraStream(int camera) {
	cv::VideoCapture capture(camera);
	if (!capture.isOpened()) {
		std::cout<<"Couldnt open the camera"<<std::endl;
		exit(EXIT_FAILURE);
	}
	return capture;
}

// create a new display window 
void createDisplay(std::string windowName) {
	cv::namedWindow(windowName, CV_WINDOW_KEEPRATIO);
}

// display the given frame in an already existing window
void displayFrame(std::string windowName, cv::Mat frame) {
	if (!frame.empty()) {
		cv::imshow(windowName, frame);
	}
}

// save a video frame as a png image
void saveFrame(cv::Mat frame) {
	std::stringstream ss;
	ss << imageCount++;

	std::string filename = "capture.png";
	//	+  ss.str()
	//	+ ".png";
	cv::imwrite(filename,frame);
}

// open a single image
cv::Mat openImage(char* fileName) {
	cv::Mat image = cv::imread(fileName, CV_LOAD_IMAGE_COLOR);
	if (!image.data) {
		std::cout << fileName << " failed to open" << std::endl;
		exit(EXIT_FAILURE);
	} else {
		std::cout << fileName << " opened successfully" << std::endl;
		return image;
	}
}

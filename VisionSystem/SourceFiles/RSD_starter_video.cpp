/*
* RSD_starter_video.cpp
*
* This code was developed for students studying RME40003 Robot Systems Design at Swinburne
* University of Technology in Melbourne, Australia
* 
* This code is largely based on the 'starter_video.cpp' code created by Ethan Rublee, Nov 23, 
* 2010 for use with OpenCV software. Ethan Rublee's code comes packaged with the OpenCV files 
* and can be found in ..\OpenCV\sources\samples\cpp\
*
* This is a simple starter sample  for using opencv, getting a video stream, displaying images,
* reading and outputting pixel values, and modifying pixel values.
* 
*/

/*
* CODE MODIFICATIONS AND BUG FIXES
* 24/07/2014 Code added by Michelle Dunn to read, output and modify pixel values
* 21/08/2014 Comments added by Michelle Dunn for Swinburne students
*/

#include "opencv2/highgui/highgui.hpp"
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <stdio.h>

#using <system.dll>
using namespace System;
#using <mscorlib.dll>
using namespace System::IO::Ports;
using namespace cv;
using namespace std;




//hide the local functions in an anon namespace
namespace {
    void help(char** av) {
        cout << "\nThis program justs gets you started reading images from video\n"
            "Usage:\n./" << av[0] << " <video device number>\n"
            << "q,Q,esc -- quit\n"
            << "space   -- save frame\n\n"
            << "\tThis is a starter sample, to get you up and going in a copy pasta fashion\n"
            << "\tThe program captures frames from a camera connected to your computer.\n"
            << "\tTo find the video device number, try ls /dev/video* \n"
            << "\tYou may also pass a video file, like my_vide.avi instead of a device number"
            << endl;
    }

    int process(VideoCapture& capture) {
        int n = 0;
        char filename[200];
        string window_name = "video | q or esc to quit";
        cout << "press space to save a picture. q or esc to quit" << endl;
        namedWindow(window_name, CV_WINDOW_KEEPRATIO); //resizable window;
        Mat frame;
        for (;;) {
            capture >> frame;
            if (frame.empty())
                break;

			/****************** Entry point for Swinburne RSD students ****************/

			// save an image
			imwrite("C:\\Users\\9504834\\Desktop\\test.png", frame);


			/*The code contained here reads and outputs a single pixel value at (10,15)*/
			Vec3b intensity = frame.at<Vec3b>(10,15);    
			int blue = intensity.val[0];
			int green = intensity.val[1];
			int red = intensity.val[2];
			cout << "Intensity = " << endl << " " << blue << " " << green << " " << red << endl << endl;
			/*End of modifying pixel values*/

			/*The code contained here modifies the output pixel values*/
			/* Modify the pixels of the RGB image */
			
			// iterate over pixels in the image
			for (int i=0; i<frame.rows; i++)
			{
				for (int j=0; j<frame.cols; j++)
				{
					if (frame.at<Vec3b>(i,j)[2] > 128) {
					 
					
					/*The following lines make the red and blue channels zero
					(this section of the image will be shades of green)*/
					frame.at<Vec3b>(i,j)[0] = 0;  // blue
					frame.at<Vec3b>(i,j)[2] = 0;  // red          
					frame.at<Vec3b>(i,j)[1] = 0;  // green
				
					}

				}
			}
			/*End of modifying pixel values*/

			/****************** End of Swinburne modifications ****************/

            imshow(window_name, frame);
            char key = (char)waitKey(5); //delay N millis, usually long enough to display and capture input
            switch (key) {
        case 'q':
        case 'Q':
        case 27: //escape key
            return 0;
        case ' ': //Save an image
            sprintf(filename,"filename%.3d.jpg",n++);
            imwrite(filename,frame);
            cout << "Saved " << filename << endl;
            break;
        default:
            break;
            }
        }
        return 0;
    }

	void writeToPort(int msg) {
		Console::WriteLine("Opening port");
		array<unsigned char>^ texBufArray = gcnew array<unsigned char>(1); 
		int baudRate=9600;
		// robot interpreter box settings
		SerialPort^ robot_int;
		// device manager/ports/USB serial port
		robot_int = gcnew SerialPort("COM4", baudRate);
		// open port
		try
		{
			// Open port to robot interpreter box
			robot_int->Open();

			// Set number to send to the port
			texBufArray[0] = msg;
	
			// Write number to the port
			robot_int->Write(texBufArray, 0, 1);

			// close port to robot interpreter box
			robot_int->Close();
		}
		catch (IO::IOException^ e) 
		{ 
			Console::WriteLine(e->GetType()->Name+": Port is not ready");
		}

	}

}

int main(int ac, char** av) {

	writeToPort(255);

    if (ac != 2) {
        help(av);
        return 1;
    }
    std::string arg = av[1];
    VideoCapture capture(arg); //try to open string, this will attempt to open it as a video file
    if (!capture.isOpened()) //if this fails, try to open as a video camera, through the use of an integer param
        capture.open(atoi(arg.c_str()));
    if (!capture.isOpened()) {
        cerr << "Failed to open a video device or video file!\n" << endl;
        help(av);
        return 1;
    }
    return process(capture);
}

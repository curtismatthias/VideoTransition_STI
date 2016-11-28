#include <iostream>
#include <algorithm>
#include <vector>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;


int main() {

	// video source
	string filename = "test3.mp4";
	VideoCapture cap(filename);

	// video specifications
	int totalFrames = cap.get(CV_CAP_PROP_FRAME_COUNT);
	int frameWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	int frameHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	int x_center = frameWidth/2;
	int y_center = frameHeight/2;

	// matrices
	Mat frame;
	Mat STI_init;
	Mat STI_col;
	Mat STI_row;

	// initialize STI matrices to frame template
	cap >> STI_init;
	cap >> STI_col;
	cap >> STI_row;

	// check if video file is valid
	if(!cap.isOpened()){
		std::cout << "\nVideo File Cannot be Opened" << std::endl;
		std::cout << "\nPress Enter to Exit..." << std::endl;
		std::cin.get();
		return 1;
	}

	// resize STI matrices to correct resolution
	resize(STI_init, STI_col, Size(totalFrames-3, frameHeight));
	resize(STI_init, STI_row, Size(totalFrames-3, frameWidth));

	// initialize STI images to black
	Vec3b black; black[0] = 0; black[1] = 0; black[2] = 0; // define black pixel (0, 0, 0)
	for(int i = 0; i < totalFrames-3;  i++){
		for(int j = 0; j < frameHeight;  j++){
			STI_col.at<Vec3b>(Point(i,j)) = black;
		}
		for(int j = 0; j < frameWidth;  j++){
			STI_row.at<Vec3b>(Point(i,j)) = black;
		}
	}

	// determine if frame is larger in x or y
	int STIsize;
	if(frameWidth > frameHeight){
		STIsize = frameWidth;
	}
	else{
		STIsize = frameHeight;
	}

	int frameNum = 0; // current frame number

	// loop through every frame of the video source
	while(waitKey(30) != 27 && totalFrames>3){
		cap >> frame;
		imshow("Video Source", frame);
		totalFrames--;

		// loop through all pixels in column/row
		for(int i = 0; i < STIsize;  i++){
			int y = i;
			int x = i;

			// set STI column (in STI_col) based on column of the frame
			if(i < frameHeight){
				Vec3b pixel = frame.at<Vec3b>(Point(x_center,y));
				STI_col.at<Vec3b>(Point(frameNum,i)) = pixel;
				imshow("STI (Column)", STI_col);
			}

			// set STI column (in STI_row) based on row of the frame
			if(i < frameWidth){
				Vec3b pixel = frame.at<Vec3b>(Point(x,y_center));
				STI_row.at<Vec3b>(Point(frameNum,i)) = pixel;
				imshow("STI (Row)", STI_row);
			}
		}

		frameNum++;
	}

	std::cout << "Press Enter to Exit..." << std::endl; // STI generation complete
	std::cin.get();

	return 0;
}
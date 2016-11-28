#include <iostream>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <algorithm>
#include <vector>

using namespace std;
using namespace cv;

int main() {

	Mat frame;
	string filename;

	filename = "test.mp4";

	VideoCapture cap(filename);

	int totalFrames = cap.get(CV_CAP_PROP_FRAME_COUNT);
	int frameWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	int frameHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

	Mat STI_init;
	Mat STI;

	if(!cap.isOpened()){
		cout << "Video cannot be opened" << endl;
		return 1;
	}

	int x = frameWidth/2;
	int y;
	int f = 0; // frames of video

	cap >> STI_init;
	cap >> STI;
	resize(STI_init, STI, Size(totalFrames, frameHeight));

	while(waitKey(30) != 27 && totalFrames>2){
		cap >> frame;
		imshow("Video", frame);
		totalFrames--;

		for(int i = 0; i < frameHeight;  i++){
			y = i;
		    Vec3b pixel = frame.at<Vec3b>(Point(x,y));
			STI.at<Vec3b>(Point(f,i)) = pixel;
			imshow("STI", STI);
		}

		f++;
	}

	//namedWindow("STI", CV_WINDOW_AUTOSIZE);

	/*for (std::vector<Vec3b>::iterator i = STIimage.begin(); i != STIimage.end(); i++){
		cout << *i << endl;
	}*/

	cout << "Press Enter to Exit..." << endl;
	cin.get();
	return 0;
}
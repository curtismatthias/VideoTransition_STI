//#include "opencv2/core/core.hpp"
//#include "opencv2/highgui.hpp"
//#include "opencv2/opencv.hpp"

#include <iostream>
#include "GetFile.h"
using namespace std;

int main() {
	cout << "Please select a file to load:" << endl;
	char videoFilename[1024];
	GetFile(videoFilename, 1024);
	if (videoFilename[0] == '\0')
	{
		fprintf(stderr, "Please select a file\n");
		return EXIT_FAILURE;
	}

	//VideoCapture vc = VideoCapture(videoFilename);
}
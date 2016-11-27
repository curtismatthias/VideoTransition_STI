#include <iostream>
#include "GetFile.h"
#include "ImageHelper.h"
#include "core.hpp"
#include "highgui.hpp"
#include "opencv.hpp"

using namespace std;
using namespace cv;

int main() {
	cout << "Please select a file to load:" << endl;
	char videoFilename[1024];
	GetFile(videoFilename, 1024);
	if (videoFilename[0] == '\0')
	{
		fprintf(stderr, "Please select a file\n");
		return EXIT_FAILURE;
	}

	VideoCapture vc = VideoCapture(videoFilename);
}
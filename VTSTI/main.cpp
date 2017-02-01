////////////////////////////////////////////////
//                                            //
//    CMPT 365 - PROJECT                      //
//                                            //
//    AUTHORS: CURTIS MATTHIAS, BEAU GRIER    //
//                                            //
////////////////////////////////////////////////


#include <iostream>
#include <algorithm>
#include <vector>

#include "GetFile.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

typedef vector<vector<double>> Matrix;
typedef vector<double> Row;


// determines the rg chromaticity red value of a pixel
double rConvert(Vec3b pixel){

	Vec3b chromaPixel;
	double chromaR = 0;

	if(pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 0){ // handles black pixel values
		chromaR = 0;
	}
	else{
		// extract RGB values from pixel
		double r = pixel[2];
		double g = pixel[1];
		double b = pixel[0];

		// convert G to chromaticity colour-space
		double sum = (r + g + b);
		chromaR = (r / sum);
	}

	return chromaR;
}


// determines the rg chromaticity green value of a pixel
double gConvert(Vec3b pixel){

	Vec3b chromaPixel;
	double chromaG = 0;

	if(pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 0){ // handles black pixel values
		chromaG = 0;
	}
	else{
		// extract RGB values from pixel
		double r = pixel[2];
		double g = pixel[1];
		double b = pixel[0];

		// convert G to chromaticity colour-space
		double sum = (r + g + b);
		chromaG = (g / sum);
	}

	return chromaG;
}


// generates a column of the histogram STI based on the current and previous frame
vector<double> histogramCompare(Mat frameCurrent, Mat framePrevious){
	
	vector<double> intersectionCol(frameCurrent.cols);

	// resize frames to 32x32 resolution for faster processing and noise removal
	resize(frameCurrent, frameCurrent, Size(32, 32));
	resize(framePrevious, framePrevious, Size(32, 32));

	// frame specifications
	double sizeOfData = frameCurrent.rows;
	double binSize = 1 + (floor(log(sizeOfData)/log(2)));

	for(int column = 0; column < frameCurrent.cols; column++){ // iterate through each column of the frames
		
		Matrix histogramCurrent; // histogram for the current frame
		Matrix histogramPrevious; // histogram for the previous frame

		// initialize histograms to contain a binSize x binSize matrix of 0s
		for(int i = 0; i < binSize; i++){
			Row row(binSize);
			for(int j = 0; j < binSize; j++){
				row[j] = 0;
			}
			histogramCurrent.push_back(row);
			histogramPrevious.push_back(row);
		}

		// generate rg values in histogramCurrent
		for(int pixelNumber = 0; pixelNumber < sizeOfData; pixelNumber++){
			for(int rBin = 0; rBin < binSize; rBin++){
				if(rConvert(frameCurrent.at<Vec3b>(Point(column, pixelNumber))) >= double((1/binSize)*(rBin)) && rConvert(frameCurrent.at<Vec3b>(Point(column, pixelNumber))) < double((1/binSize)*(rBin+1))){
					for(int gBin = 0; gBin < binSize; gBin++){
						if(gConvert(frameCurrent.at<Vec3b>(Point(column, pixelNumber))) >= double((1/binSize)*(gBin)) && gConvert(frameCurrent.at<Vec3b>(Point(column, pixelNumber))) < double((1/binSize)*(gBin+1))){
							histogramCurrent[rBin][gBin]++;
						}
					}
				}
			}
		}

		// generate rg values in histogramPrevious
		for(int pixelNumber = 0; pixelNumber < sizeOfData; pixelNumber++){
			for(int rBin = 0; rBin < binSize; rBin++){
				if(rConvert(framePrevious.at<Vec3b>(Point(column, pixelNumber))) >= double((1/binSize)*(rBin)) && rConvert(framePrevious.at<Vec3b>(Point(column, pixelNumber))) < double((1/binSize)*(rBin+1))){
					for(int gBin = 0; gBin < binSize; gBin++){
						if(gConvert(framePrevious.at<Vec3b>(Point(column, pixelNumber))) >= double((1/binSize)*(gBin)) && gConvert(framePrevious.at<Vec3b>(Point(column, pixelNumber))) < double((1/binSize)*(gBin+1))){
							histogramPrevious[rBin][gBin]++;
						}
					}
				}
			}
		}

		// divide each histogram by its sum, so that each adds up to unity
		for(int i = 0; i < binSize; i++){
			for(int j = 0; j < binSize; j++){
				histogramCurrent[i][j] = histogramCurrent[i][j] / sizeOfData;
				histogramPrevious[i][j] = histogramPrevious[i][j] / sizeOfData;
			}
		}

		// for each array entry, add up the smaller of the values at that array location, over the two histograms being compared (histogram intersection)
		double hComparison = 0;
		for(int i = 0; i < binSize; i++){
			for(int j = 0; j < binSize; j++){
				hComparison = hComparison + min(histogramCurrent[i][j], histogramPrevious[i][j]);
			}
		}

		intersectionCol[column] = hComparison; // add histogram comparison value to the histrogram STI column
	}

	return intersectionCol;
}


int main() {

	// interface variables
	bool interface = true;
	int menu = 0;

	// intro messaging
	cout << "Video Transition Spatio-Temporal Images" << endl << endl;
	cout << "Please select an video file" << endl;

	// file picker
	char filename[1024];
	GetFile(filename, 1024);
	if (filename[0] == '\0')
	{
		fprintf(stderr, "Please select a file\n");
		return EXIT_FAILURE;
	}

	// video source
	string str(filename);
	VideoCapture cap(str);

	// begin interface loop
	while (interface == true){

		VideoCapture cap(str);

		// menu messaging
		cout << endl << "Please select an option:" << endl;
		cout << "STI by Copying Columns - 1" << endl;
		cout << "STI by Copying Rows - 2" << endl;
		cout << "STI by Histogram Differences - 3" << endl;
		cout << "Select Another Video File - 4" << endl;
		cout << "Exit - 5" << endl;
		cin >> menu;	

		// menu input - 4, new video file
		if(menu == 4){

			cap.release();

			// file picker
			char filename[1024];
			GetFile(filename, 1024);
			if (filename[0] == '\0')
			{
				fprintf(stderr, "Please select a file\n");
				return EXIT_FAILURE;
			}

			// video source
			str = filename;
			VideoCapture cap(str);
		}
		// menu input - 5, exit
		else if(menu == 5){
			cap.release(); // close the video file

			return 0;
		}
		else{
			if(menu == 1 || menu == 2 || menu == 3){
				// video specifications
				int totalFrames = cap.get(CV_CAP_PROP_FRAME_COUNT);
				int frameWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
				int frameHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
				int x_center = frameWidth/2;
				int y_center = frameHeight/2;

				// matrices
				Mat frame;
				Mat framePrev;
				Mat STI_init;
				Mat STI_col;
				Mat STI_row;
				Mat STI_histogram;

				// initialize STI matrices to frame template
				cap >> STI_col;
				cap >> STI_row;
				cap >> STI_histogram;

				// check if video file is valid
				if(!cap.isOpened()){
					std::cout << "\nVideo File Cannot be Opened" << std::endl;
					std::cout << "\nPress Enter to Exit..." << std::endl;
					std::cin.get();
					return 1;
				}

				// resize STI matrices to correct resolution
				resize(STI_col, STI_col, Size(totalFrames, frameHeight));
				resize(STI_row, STI_row, Size(totalFrames, frameWidth));
				resize(STI_histogram, STI_histogram, Size(totalFrames, 32));

				// initialize STI images to black
				Vec3b black; black[0] = 0; black[1] = 0; black[2] = 0; // define black pixel (0, 0, 0)
				for(int i = 0; i < totalFrames;  i++){
					for(int j = 0; j < frameHeight;  j++){
						STI_col.at<Vec3b>(Point(i,j)) = black;
					}
					for(int j = 0; j < frameWidth;  j++){
						STI_row.at<Vec3b>(Point(i,j)) = black;
					}
					for(int j = 0; j < 32;  j++){
						STI_histogram.at<Vec3b>(Point(i,j)) = black;
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
				cap >> framePrev;

				// loop through every frame of the video source
				while(waitKey(1) != 27 && frameNum < totalFrames){

					cap >> frame;

					if(frame.data != NULL){

						imshow("Video Source", frame); // display video source
						
						// menu input - 3, histogram
						if(menu == 3){
							// histogram
							vector<double> histogramCol = histogramCompare(frame, framePrev);
							for(int i = 0; i < STI_histogram.rows; i++){
								Vec3b tempPixel;
								tempPixel[0] = histogramCol[i]*255;
								tempPixel[1] = histogramCol[i]*255;
								tempPixel[2] = histogramCol[i]*255;
								STI_histogram.at<Vec3b>(Point(frameNum,i)) = tempPixel;
							}
							Mat STI_histogramLarge;
							resize(STI_histogram, STI_histogramLarge, Size(totalFrames, 128));
							imshow("STI by Histogram Differences", STI_histogramLarge);
						}
						else if(menu == 1 || menu == 2){
							// loop through all pixels in column/row
							for(int i = 0; i < STIsize;  i++){
								int y = i;
								int x = i;

								// menu input - 1, STI by column
								if(menu == 1){
									// set STI column (in STI_col) based on column of the frame
									if(i < frameHeight){
										Vec3b pixel = frame.at<Vec3b>(Point(x_center,y));
										STI_col.at<Vec3b>(Point(frameNum,i)) = pixel;
										imshow("STI by Copying Columns", STI_col);
									}
								}
								// menu input - 2, STI by row
								else if(menu == 2){
									// set STI column (in STI_row) based on row of the frame
									if(i < frameWidth){
										Vec3b pixel = frame.at<Vec3b>(Point(x,y_center));
										STI_row.at<Vec3b>(Point(frameNum,i)) = pixel;
										imshow("STI by Copying Rows", STI_row);
									}
								}
							}
						}

						framePrev = frame.clone(); // clones a frame for use in histogram

						frameNum++;

					}
					else{
						break;
					}
				}
			}
			else{
				cout << endl << "Not a Valid Input" << endl << endl; //  incorrect error messaging
			}
		}

		// handles incorrect input, clears input
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
}
// END
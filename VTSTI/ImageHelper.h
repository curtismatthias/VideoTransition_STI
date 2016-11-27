#pragma once
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;
class ImageHelper
{
public:
	static Mat ImageHelper::convertImage(Mat image);
	static void ImageHelper::printColumn(Mat image);

};

#ifndef _MYIMAGE_
#define _MYIMAGE_ 

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

class MyImage{
	public:
		MyImage(int webCamera);
		MyImage();
		
		VideoCapture cap; // obiekt kamery
		Mat srcLR; // obraz w mniejszej rozdzielczosci
		Mat src; // obraz
		Mat bw; // obraz binarny
		vector<Mat> bwList; // wektor obrazow binarnych
};

#endif

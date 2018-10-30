#ifndef COLOR_
#define COLOR_

#include "roi.hpp"
#include "myImage.hpp"
#include <string>

using namespace std;
using namespace cv;

class Color {
	int c_upper[7][3];
	int fontFace = FONT_HERSHEY_PLAIN; // czcionka Plain
	int square_len; // dlugosc boku kwadratu
	int avgColor[7][3];
	int c_lower[7][3];
	vector <My_ROI> roi;
public:
	Color();
	void printText(Mat, string);
	void waitForPalmCover(MyImage*);
	int getMedian(vector<int>);
	void getAvgColor(MyImage *, My_ROI, int avg[3]);
	void average(MyImage *);
	void initTrackbars();
	void normalizeColors(MyImage *);
	void produceBinaries(MyImage *);
	void initWindows(MyImage);
	void showWindows(MyImage);
};

#endif // !COLOR

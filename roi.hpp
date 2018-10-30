#ifndef ROI 
#define ROI


#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;

class My_ROI{
	Point upper_corner, lower_corner; // wspolrzene gornego i dolnego naroznika
	Mat roi_ptr; // miejsce na obraz ROI
	Scalar color; // kolor
	int border_thickness; // grubosc linii 
public:
		My_ROI(); // konstruktor domyslny
		My_ROI(Point upper_corner, Point lower_corner,Mat src); // konstruktor paramrtryzowany
		void draw_rectangle(Mat src); // dunkcja rysowania prostokata
		Mat return_roi();
};

#endif

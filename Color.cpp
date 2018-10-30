#include "Color.hpp"

Color::Color() {
	square_len = 20;
}

void Color::printText(Mat src, string text) {
	putText(src, text, Point(src.cols / 2, src.rows / 10), fontFace, 1.2f, Scalar(200, 0, 0), 2);
}

void Color::waitForPalmCover(MyImage* m) {
	m->cap >> m->src; // odczyt video 
	flip(m->src, m->src, 1); // obrot wokol osi y 
	roi.push_back(My_ROI(Point(m->src.cols / 3, m->src.rows / 6), Point(m->src.cols / 3 + square_len, m->src.rows / 6 + square_len), m->src));
	roi.push_back(My_ROI(Point(m->src.cols / 4, m->src.rows / 2), Point(m->src.cols / 4 + square_len, m->src.rows / 2 + square_len), m->src));
	roi.push_back(My_ROI(Point(m->src.cols / 3, m->src.rows / 1.5), Point(m->src.cols / 3 + square_len, m->src.rows / 1.5 + square_len), m->src));
	roi.push_back(My_ROI(Point(m->src.cols / 2, m->src.rows / 2), Point(m->src.cols / 2 + square_len, m->src.rows / 2 + square_len), m->src));
	roi.push_back(My_ROI(Point(m->src.cols / 2.5, m->src.rows / 2.5), Point(m->src.cols / 2.5 + square_len, m->src.rows / 2.5 + square_len), m->src));
	roi.push_back(My_ROI(Point(m->src.cols / 2, m->src.rows / 1.5), Point(m->src.cols / 2 + square_len, m->src.rows / 1.5 + square_len), m->src));
	roi.push_back(My_ROI(Point(m->src.cols / 2.5, m->src.rows / 1.8), Point(m->src.cols / 2.5 + square_len, m->src.rows / 1.8 + square_len), m->src));


	for (int i = 0; i<50; i++) {
		m->cap >> m->src;
		flip(m->src, m->src, 1);
		for (int j = 0; j<7; j++) {
			roi[j].draw_rectangle(m->src);
		}
		string imgText = string("Cover rectangles with palm");
		printText(m->src, imgText);

		imshow("img1", m->src);
		if (cv::waitKey(30) >= 0) break;
	}
}

int Color::getMedian(vector<int> val) {
	int median;
	size_t size = val.size();
	sort(val.begin(), val.end());
	if (size % 2 == 0)
		median = val[size / 2 - 1];
	else
		median = val[size / 2];
	return median;
}

void Color::getAvgColor(MyImage *m, My_ROI roi, int avg[3]) {
	Mat r;
	roi.return_roi().copyTo(r);
	vector<int>hm;
	vector<int>sm;
	vector<int>lm;
	// generate vectors
	for (int i = 2; i<r.rows - 2; i++) {
		for (int j = 2; j<r.cols - 2; j++) {
			hm.push_back(r.data[r.channels()*(r.cols*i + j) + 0]);
			sm.push_back(r.data[r.channels()*(r.cols*i + j) + 1]);
			lm.push_back(r.data[r.channels()*(r.cols*i + j) + 2]);
		}
	}
	avg[0] = getMedian(hm);
	avg[1] = getMedian(sm);
	avg[2] = getMedian(lm);
}

void Color::average(MyImage *m) {
	m->cap >> m->src;
	flip(m->src, m->src, 1);
	for (int i = 0; i<30; i++) {
		m->cap >> m->src;
		flip(m->src, m->src, 1);
		cvtColor(m->src, m->src, CV_BGR2HLS);
		for (int j = 0; j<7; j++) {
			getAvgColor(m, roi[j], avgColor[j]);
			roi[j].draw_rectangle(m->src);
		}
		cvtColor(m->src, m->src, CV_HLS2BGR);
		string imgText = string("Finding average color of hand");
		printText(m->src, imgText);
		imshow("img1", m->src);
		if (cv::waitKey(30) >= 0) break;
	}
}

void Color::initTrackbars() {
	for (int i = 0; i<7; i++) {
		c_lower[i][0] = 44;
		c_upper[i][0] = 10;
		c_lower[i][1] = 31;
		c_upper[i][1] = 161;
		c_lower[i][2] = 47;
		c_upper[i][2] = 173;
	}
	createTrackbar("Hue Lower", "trackbars", &c_lower[0][0], 255);
	createTrackbar("Saturation Lower", "trackbars", &c_lower[0][1], 255);
	createTrackbar("Value Lower", "trackbars", &c_lower[0][2], 255);
	createTrackbar("Hue Upper", "trackbars", &c_upper[0][0], 255);
	createTrackbar("Saturation Upper", "trackbars", &c_upper[0][1], 255);
	createTrackbar("Value Upper", "trackbars", &c_upper[0][2], 255);
}


void Color::normalizeColors(MyImage * myImage) {
	// copy all boundries read from trackbar
	// to all of the different boundries
	for (int i = 1; i<7; i++) {
		for (int j = 0; j<3; j++) {
			c_lower[i][j] = c_lower[0][j];
			c_upper[i][j] = c_upper[0][j];
		}
	}
	// normalize all boundries so that 
	// threshold is whithin 0-255
	for (int i = 0; i<7; i++) {
		if ((avgColor[i][0] - c_lower[i][0]) <0) {
			c_lower[i][0] = avgColor[i][0];
		}if ((avgColor[i][1] - c_lower[i][1]) <0) {
			c_lower[i][1] = avgColor[i][1];
		}if ((avgColor[i][2] - c_lower[i][2]) <0) {
			c_lower[i][2] = avgColor[i][2];
		}if ((avgColor[i][0] - c_upper[i][0]) >0) {
			c_upper[i][0] = avgColor[i][0];
		}if ((avgColor[i][1] - c_upper[i][1]) >0) {
			c_upper[i][1] = avgColor[i][1];
		}if ((avgColor[i][2] - c_upper[i][2]) >0) {
			c_upper[i][2] = avgColor[i][2];
		}
	}
}

void Color::produceBinaries(MyImage *m) {
	Scalar lowerBound;
	Scalar upperBound;
	Mat foo;
	for (int i = 0; i<7; i++) {
		normalizeColors(m);
		lowerBound = Scalar(avgColor[i][0] - c_lower[i][0], avgColor[i][1] - c_lower[i][1], avgColor[i][2] - c_lower[i][2]); // dolna granica
		upperBound = Scalar(c_upper[i][0], c_upper[i][1], c_upper[i][2]); // gorna granica
		m->bwList.push_back(Mat(m->srcLR.rows, m->srcLR.cols, CV_8U));
		inRange(m->srcLR, lowerBound, upperBound, m->bwList[i]);	// progowanie
	}
	m->bwList[0].copyTo(m->bw);
	for (int i = 1; i<7; i++) {
		m->bw += m->bwList[i];
	}
	medianBlur(m->bw, m->bw, 7); // filtr medianowy 7x7
}

void Color::initWindows(MyImage m) {
	namedWindow("trackbars", CV_WINDOW_KEEPRATIO);
	namedWindow("img1", CV_WINDOW_FULLSCREEN);
}

void Color::showWindows(MyImage m) {
	pyrDown(m.bw, m.bw);
	pyrDown(m.bw, m.bw); // zmniejszanie rozmiaru
	Rect roi(Point(3 * m.src.cols / 4, 0), m.bw.size()); // umiejscowienie w prawym gornym rogu	
	vector<Mat> channels;
	Mat result;
	for (int i = 0; i<3; i++)
		channels.push_back(m.bw);
	merge(channels, result);
	result.copyTo(m.src(roi));
	imshow("img1", m.src);
}

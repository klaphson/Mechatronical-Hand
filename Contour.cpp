#include "Contour.hpp"


int Contour::findBiggestContour(vector<vector<Point> > contours) {
	int indexOfBiggestContour = -1;
	int sizeOfBiggestContour = 0;
	for (int i = 0; i < contours.size(); i++) {
		if (contours[i].size() > sizeOfBiggestContour) {
			sizeOfBiggestContour = contours[i].size();
			indexOfBiggestContour = i;
		}
	}
	return indexOfBiggestContour;
}

void Contour::myDrawContours(MyImage *m, HandGesture *hg) {
	drawContours(m->src, hg->hullP, hg->cIdx, cv::Scalar(200, 0, 0), 2, 8, vector<Vec4i>(), 0, Point());
	rectangle(m->src, hg->bRect.tl(), hg->bRect.br(), Scalar(0, 0, 200));
}

void Contour::makeContours(MyImage *m, HandGesture* hg, Maestro maestro) {
	Mat aBw;
	pyrUp(m->bw, m->bw); // zwiekszenie rozdzielczosci obrazu
	m->bw.copyTo(aBw);
	findContours(aBw, hg->contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	hg->initVectors();
	hg->cIdx = findBiggestContour(hg->contours);
	if (hg->cIdx != -1) {
		approxPolyDP(Mat(hg->contours[hg->cIdx]), hg->contours[hg->cIdx], 11, true); // przyblizanie wykrytego konturu wielokatem
		hg->bRect = boundingRect(Mat(hg->contours[hg->cIdx])); // dla bRect przypisujemy prostokat otaczajacy nasz kontur
		convexHull(Mat(hg->contours[hg->cIdx]), hg->hullP[hg->cIdx], false, true); //znajdowanie obwiedni konturu w postaci vektora punktow
		convexHull(Mat(hg->contours[hg->cIdx]), hg->hullI[hg->cIdx], false, false); // znajdowanie obwiedni konturu w postaci vektora indeksow
		approxPolyDP(Mat(hg->hullP[hg->cIdx]), hg->hullP[hg->cIdx], 11, true); // przyblizanie wykrytej obwiedni wielokatem
		if (hg->contours[hg->cIdx].size()>3) {
			convexityDefects(hg->contours[hg->cIdx], hg->hullI[hg->cIdx], hg->defects[hg->cIdx]);
			hg->eleminateDefects(m);
		}
		bool isHand = hg->detectIfHand();
		hg->printGestureInfo(m->src);
		if (isHand) {
			hg->getFingerTips(m); // utworzenie wktora punktow z koncwokami palcow
			if(maestro.returnServos() == true) 
			{
			

			if(hg->fingerTips.size() == 0)
			{
				for(int i = 0; i < 5; i++)
				{
					//int position = maestro.maestroGetPosition(i);
					if (i==0)
					{
					int target = 9600;
					maestro.maestroSetTarget(i, target);
				}
				if(i==1){
					int target = 9600;
					maestro.maestroSetTarget(i, target);
				}
				if(i==2){
					int target = 3328;
					maestro.maestroSetTarget(i, target);
				}
				if(i==3){
					int target = 9600;
					maestro.maestroSetTarget(i, target);
				}
				if(i==4){
					int target = 9408;
					maestro.maestroSetTarget(i, target);
				}
			  }
		  }
			else
			{
				for(int i = 0; i < hg->fingerTips.size(); i++)
			    {
					if(i == 0) {
						
					    int target = 9408;
				        maestro.maestroSetTarget(2, target);
					}
					if(i==1) {
						int target = 1856;
						maestro.maestroSetTarget(0, target);
					}
					if(i==2) {
						int target = 2176;
						maestro.maestroSetTarget(1, target);
					}
					if(i==3) {
						int target = 2176;
						maestro.maestroSetTarget(i, target);
					}		
					if(i==4) {
						int target = 1984;
						maestro.maestroSetTarget(i, target);
					}				
			    }
			    for(int i = hg->fingerTips.size(); i < 5; i++)
			    {
					if(i==1) {
						int target = 9600;
						maestro.maestroSetTarget(0, target);
					}
					if(i==2) {
						int target = 9600;
						maestro.maestroSetTarget(1, target);
					}
					if(i==3) {
						int target = 9600;
						maestro.maestroSetTarget(3, target);
					}
					if(i==4) {
						int target = 9408;
						maestro.maestroSetTarget(4, target);
					}
				}
		    }
		}
			hg->drawFingerTips(m); // rysowanie koncowek palcow 
			myDrawContours(m, hg);
		}
	}
}

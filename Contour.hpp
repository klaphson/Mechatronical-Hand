#ifndef CONTOUR
#define CONTOUR

#include "handGesture.hpp"
#include "maestro.hpp"


class Contour {
public:
	int findBiggestContour(vector<vector<Point> >);
	void myDrawContours(MyImage *, HandGesture *);
	void makeContours(MyImage *, HandGesture*, Maestro);
};
#endif // !COLOR

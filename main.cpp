#include "Color.hpp"
#include "Contour.hpp"

using namespace cv;
using namespace std;


int main(){
	const char * device = "/dev/ttyACM0";
    int fd = open(device, O_RDWR | O_NOCTTY);
      if (fd == -1)
  {
    perror(device);
    return 1;
  }
	Maestro maestro(fd);
	MyImage m(0);	// stworzenie obiektu MyImage, wybor kamery i pobranie obrazu
	HandGesture hg; // stowrzenie obiektu HandGesture
	Color c;
	Contour cont;
	m.cap >> m.src; // pobranie obrazu z kamery do src
    namedWindow("img1",CV_WINDOW_AUTOSIZE); // stworzenie okna img1
	c.waitForPalmCover(&m); // odczekanie na umieszczenie dloni w odpowiednim miejscu
	c.average(&m); // pobranie sredniej wartosci barw dloni
	destroyWindow("img1"); // zniszczenie okna img1
	c.initWindows(m); //stworzenie okien obrazu i trackbarow
	c.initTrackbars(); //inicjalizacja trackbarow
	for(;;){
		m.cap >> m.src; //pobranie klatki
		flip(m.src,m.src,1); //obrot wokol osi y
		pyrDown(m.src,m.srcLR); //zmniejszenie rozdzielczosci obrazu i zapis do srcLR
		blur(m.srcLR,m.srcLR,Size(3,3)); // rozmycie obrazu za pomoca filtra skrzynowego 3x3
		cvtColor(m.srcLR,m.srcLR,CV_BGR2HLS); // zamiana przestrzeni barw z BGR NA HSV
		c.produceBinaries(&m); // stworzenie obrazu binarnego
		cvtColor(m.srcLR,m.srcLR,CV_HLS2BGR); // powrot z przestrzeni barw HSV na BGR
		cont.makeContours(&m, &hg, maestro); // stworzenie konturu
		c.showWindows(m);
    	if(cv::waitKey(30) == char('q')) break;
    	if(cv::waitKey(30) == char('s')) maestro.startServos();
	}
	destroyAllWindows();
	m.cap.release();
    return 0;
}

#ifndef CA_IMAGE_H
#define CA_IMAGE_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "cell.hpp"
#include "grid.hpp"

#define GRID_INC 10

#define CELL_0 Scalar(0,0,0)
#define CELL_5 Scalar(255,255,255)
#define CELL_3 Scalar(128,65,230)
#define CELL_1 Scalar(0,255,255)
#define CELL_4 Scalar(128,128,128)
#define CELL_2 Scalar(0,255,0)
#define CELL_6 Scalar(0,128,0)
#define CELL_7 Scalar(0,128,128)


using namespace cv;
using namespace std;

class Image {
public:
    Image(unsigned long width, unsigned long height);
    void createImage(Grid grid, int waitKeyTime, bool showWindow);
    ~Image();

private:
    Size2d imgSize;
    unsigned long width;
    unsigned long height;

    void createPixel(Mat img, Point pixel, Scalar color);
    void createGrid(Mat img);
    double round(double var);

};


#endif //CA_IMAGE_H

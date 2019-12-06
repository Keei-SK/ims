#ifndef CA_IMAGE_H
#define CA_IMAGE_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Cell.hpp"

#define GRID_INC 20

#define CELL_WALL Scalar(0,0,0)
#define CELL_EMPTY Scalar(255,255,255)
#define CELL_PERSON Scalar(128,65,230)
#define CELL_OBSTACLE Scalar(0,255,255)
#define CELL_SMOKE_OBSTACLE Scalar(0,200,200)
#define CELL_SMOKE Scalar(128,128,128)
#define CELL_SMOKE_FIRE Scalar(0,0,128)
#define CELL_PERSON_SMOKE Scalar (100,100,100)
#define CELL_PERSON_SMOKE_FIRE Scalar(255,0,255)
#define CELL_EXIT Scalar(0,255,0)


using namespace cv;
using namespace std;

class Image {
public:
    Image(unsigned long width, unsigned long height);
    void createImage(vector<vector<Cell*>> state, double modelTime, int waitKeyTime, bool showWindow);
    ~Image();

private:
    Size2d imgSize;
    unsigned long width;
    unsigned long height;

    void createPixel(Mat img, Point pixel, Scalar color);
    void createGrid(Mat img);

};


#endif //CA_IMAGE_H

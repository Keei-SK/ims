#include "Image.h"

Image::Image(unsigned long width, unsigned long height) {
    this->imgSize = Size2d(width * GRID_INC, height * GRID_INC);
    this->width = width;
    this->height = height;
}

void Image::createGrid(Mat img) {
    line(img, Point(0, 0), Point(0, this->imgSize.height - 1), Scalar(140, 140, 140));
    for (int x = GRID_INC; x <= this->imgSize.width; x += GRID_INC) {
        line(img, Point(x, 0), Point(x, this->imgSize.height - 1), Scalar(140, 140, 140)); //vertical lines
    }

    line(img, Point(0, 0), Point(this->imgSize.width - 1, 0), Scalar(140, 140, 140));
    for (int x = GRID_INC; x < this->imgSize.height; x += GRID_INC) {
        line(img, Point(0, x), Point(this->imgSize.width - 1, x), Scalar(140, 140, 140)); //horizontal lines
    }
    line(img, Point(0, this->imgSize.height), Point(this->imgSize.width, this->imgSize.height),
         Scalar(140, 140, 140)); //last horizontal lines
}

void Image::createPixel(Mat img, Point pixel, Scalar color) {
    int x = pixel.x * GRID_INC + 1; //imagePixel_x
    int y = pixel.y * GRID_INC + 1; //imagePixel_y
    for (int i = 0; i < GRID_INC - 1; i++) {
        line(img, Point(x, y + i), Point(x + GRID_INC - 2, y + i), color);
    }
}

void Image::createImage(vector<vector<Cell*>> state, double modelTime, int waitKeyTime, bool showWindow = false) {
    Mat image = Mat(this->imgSize.height + 1, this->imgSize.width + 1, CV_8UC3, Scalar(255, 255, 255));
    this->createGrid(image);

    for (int rows = 0; rows < this->imgSize.height; rows++) {
        for (int cols = 0; cols < this->imgSize.width / GRID_INC; cols++) {
            switch((state[rows % this->height][cols])->getState()){
                case wall:
                    this->createPixel(image, Point(cols, rows), CELL_WALL);
                    break;
                case obstacle:
                    this->createPixel(image, Point(cols, rows), CELL_OBSTACLE);
                    break;
                case door:
                    this->createPixel(image, Point(cols, rows), CELL_EXIT);
                    break;
                case person:
                    this->createPixel(image, Point(cols, rows), CELL_PERSON);
                    break;
                case doorPerson :
                    this->createPixel(image, Point(cols, rows), CELL_SMOKE);
                    break;
                default:
                    this->createPixel(image, Point(cols, rows), CELL_EMPTY);
                    break;
            }
        }
    }

    if (showWindow) {
        namedWindow("Evacuation", CV_WINDOW_AUTOSIZE);
        imshow("Evacuation", image);
        //imwrite("/tmp/img.png", image);
    }
    waitKey(waitKeyTime );
}

Image::~Image() {}

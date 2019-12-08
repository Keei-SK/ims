#include "image.hpp"

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

// round double to two decimal places
double Image::round(double var)
{
    double value = (int)(var * 100 + .5);
    return (double)value / 100;
} 

void Image::createImage(Grid grid, int waitKeyTime, bool showWindow = false) {
    Mat image = Mat(this->imgSize.height + 1, this->imgSize.width + 1, CV_8UC3, Scalar(255, 255, 255));
    //this->createGrid(image);

    for(int y = 0; y <= grid.width; y++) //for row in matrix
        {
            for(int x = 0; x <= grid.width; x++) //for col in matrix
            {   
                double state = round(grid.present_grid[grid.order_from_coords(x, y)].state);
                if(state == 0.00) {
                    this->createPixel(image, Point(y, x), CELL_0);
                }
                else if(state <=0.05) {
                    this->createPixel(image, Point(y, x), CELL_1);
                }
                else if(state <= 0.10) {
                    this->createPixel(image, Point(y, x), CELL_2);
                }
                else if (state <= 0.20) {
                    this->createPixel(image, Point(y, x), CELL_3);;
                }
                else if (state <= 0.30) {
                    this->createPixel(image, Point(y, x), CELL_4);
                }
                else if (state <= 0.40) {
                    this->createPixel(image, Point(y, x), CELL_5); // bude zluta
                }
                else if (state <= 0.50) {
                    this->createPixel(image, Point(y, x), CELL_6); //bude oranzova
                }
                else
                {
                    this->createPixel(image, Point(y, x), CELL_7); //bude cervena
                }
            }
        }

    if (showWindow) {
        namedWindow("Cellular automata", CV_WINDOW_AUTOSIZE);
        imshow("Cellular automata", image);
        //imwrite("/tmp/img.png", image);
    }
    waitKey(waitKeyTime );
}

Image::~Image() {}

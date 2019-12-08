#include "image.hpp"

Image::Image(unsigned long width, unsigned long height) {
    this->imgSize = Size2d(width+GRID_INC, height+GRID_INC);
    this->width = width;
    this->height = height;
}

void Image::create_pixel(Mat img, Point pixel, Scalar color) {
    int x = pixel.x*GRID_INC;
    int y = pixel.y*GRID_INC;
    for (int i = 0; i < GRID_INC; ++i)
    {
        line(img, Point(x,y+i), Point(x+GRID_INC, y+i), color);
    }
}

// round double to two decimal places
double Image::round(double var)
{
    double value = (int)(var * 100 + .5);
    return (double)value / 100;
} 

void Image::create_image(Grid grid, int waitKeyTime, bool showWindow = false) {
    Mat image = Mat(this->imgSize.height, this->imgSize.width, CV_8UC3, Scalar(255, 255, 255));
    //this->createGrid(image);

    for(int y = 0; y <= grid.width; y++) //for row in matrix
    {
        for(int x = 0; x <= grid.width; x++) //for col in matrix
        {   
            double state = round(grid.present_grid[grid.order_from_coords(x, y)].state);
            if(state == 0.00) {
                this->create_pixel(image, Point(y, x), CELL_0);
            }
            else if(state <=0.05) {
                this->create_pixel(image, Point(y, x), CELL_1);
            }
            else if(state <= 0.10) {
                this->create_pixel(image, Point(y, x), CELL_2);
            }
            else if (state <= 0.20) {
                this->create_pixel(image, Point(y, x), CELL_3);;
            }
            else if (state <= 0.30) {
                this->create_pixel(image, Point(y, x), CELL_4);
            }
            else if (state <= 0.40) {
                this->create_pixel(image, Point(y, x), CELL_5);
            }
            else if (state <= 0.50) {
                this->create_pixel(image, Point(y, x), CELL_6);
            }
            else
            {
                this->create_pixel(image, Point(y, x), CELL_7);
            }
        }
    }

    if (showWindow) {
        namedWindow("Cellular automata", CV_WINDOW_AUTOSIZE);
        imshow("Cellular automata", image);
        //imwrite("./tmp/img.png", image);
    }
    waitKey(waitKeyTime );
}

#ifndef CELL_HPP
#define CELL_HPP

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

class Cell {
public:
    Cell(int x, int y, int density) {
        setCell(x,y,density);
    }
    Cell(void) {
        setCell(0,0,0);
    }
    void updateDensity(int density);
    void setCell(int x, int y, int density);
    int density;
    int x;
    int y;
};

#endif
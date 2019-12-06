#ifndef CELL_HPP
#define CELL_HPP

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

class Cell {
public:
    Cell(int x, int y, int state) {
        setCell(x,y,state);
    }
    Cell(void) {
        setCell(0,0,0);
    }
    void updateDensity(int state);
    void setCell(int x, int y, int state);
    int state;
    int x;
    int y;
};

#endif
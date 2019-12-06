#include "cell.hpp"

void Cell::updateDensity(int density) {
    this->density = density;
}

void Cell::setCell(int x, int y, int density) {
        this->density = density;
        this->x = x;
        this->y = y;
}
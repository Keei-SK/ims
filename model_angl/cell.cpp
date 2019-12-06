#include "cell.hpp"

void Cell::updateDensity(int state) {
    this->state = state;
}

void Cell::setCell(int x, int y, int state) {
    this->state = state;
    this->x = x;
    this->y = y;
}
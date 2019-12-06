#ifndef GRID_HPP
#define GRID_HPP

#include "cell.hpp"
#include <vector>

using namespace std;

class Grid {
public:
    Grid(int width, vector<Cell> present_grid) {
        present_grid.reserve(width);
        future_grid.reserve(width);
        this->width = width;
        this->present_grid = present_grid;
    }
    int width;
    vector<Cell> present_grid;
    vector<Cell> future_grid;
    int max_popul;
    double reproduction_rate;
    double fertility;
    double mortality;    
    int time;
};

#endif
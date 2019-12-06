#ifndef GRID_HPP
#define GRID_HPP

#include "cell.hpp"
#include <vector>

using namespace std;

class Grid {
public:
    Grid(int width) {
        int size = width*width;
        present_grid.reserve(size);
        future_grid.reserve(size);
        this->width = width;
    }
    void fill_present_grid();
    void print_present_grid();
    int order_from_coords(int x, int y);
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
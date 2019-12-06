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
    void set_params(
        double reproduction_rate, double max_population,
        double migration_param
    );
    void fill_present_grid();
    void print_present_grid();   
    int order_from_coords(int x, int y);
    Cell get_present_cell(int x, int y);
    Cell get_future_cell(int x, int y);
    void compute_future_grid();
    double compute_diffusion_operator(int x, int y);
    void copy_future_to_present_grid();

    int width;
    vector<Cell> present_grid;
    vector<Cell> future_grid;
    int time;
    int max_population;
    double fertility;
    double mortality;    
    double migration_param;
};

#endif
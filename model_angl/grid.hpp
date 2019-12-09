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
        this->max_idx = width-1;
    }
    void set_params(
        double reproduction_rate, double max_population,
        double migration_param
    );
    void init_present_grid();
    void print_present_grid();   
    int order_from_coords(int x, int y);
    Cell get_present_cell(int x, int y);
    Cell get_future_cell(int x, int y);
    void get_future_grid(int month);    
    void copy_future_to_present_grid();
    double get_average();
    double diffusion_operator(int x, int y);
    double random_double(double min, double max);
    void fill_chunk_of_present_grid(int xmin, int ymin, int width, double value);
    void set_counter_measure(int counter_measure);

    int width;
    int max_idx;
    vector<Cell> present_grid;
    vector<Cell> future_grid;
    int time;
    double max_population;
    double fertility;
    double mortality;    
    double migration_param;
    int counter_measure = 0;
};

#endif
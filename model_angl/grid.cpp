#include "grid.hpp"
#include <math.h>

/*
    for (int y = 0; y < this->width; ++y)
    {
        for (int x = 0; x < this->width; ++x)
        {
            
        }
    }
*/

void Grid::set_params(
    double reproduction_rate, double max_population,
    double migration_param
) {
    this->fertility = (1 - reproduction_rate);
    this->mortality = (-reproduction_rate/max_population);
    this->max_population = max_population;
    this->migration_param = migration_param;
}

void Grid::fill_present_grid() {
    for (int y = 0; y < this->width; ++y)
    {
        for (int x = 0; x < this->width; ++x)
        {
            // creates Cell and appends it at the end of grid
            present_grid.emplace_back(x,y,-1/this->fertility);
        }
    }
}

Cell Grid::get_present_cell(int x, int y) {
    return this->present_grid[order_from_coords(x, y)];
}

Cell Grid::get_future_cell(int x, int y) {
    return this->future_grid[order_from_coords(x, y)];
}

int Grid::order_from_coords(int x, int y) {
    return y + (x*this->width);
}

void Grid::print_present_grid() {
    for (int y = 0; y < this->width; ++y)
    {
        for (int x = 0; x < this->width; ++x)
        {
            cout << this->present_grid[order_from_coords(x, y)].state << " ";
        }
        cout << endl;
    }
    cout << endl;
}

double Grid::compute_diffusion_operator(int x, int y) {
    double diffusion_operator =
        this->present_grid[order_from_coords(x, y-1)].state +
        this->present_grid[order_from_coords(x, y+1)].state + 
        this->present_grid[order_from_coords(x+1, y)].state +
        this->present_grid[order_from_coords(x-1, y)].state +
        (4 * this->present_grid[order_from_coords(x-1, y)].state);
    return diffusion_operator; 
}

void Grid::compute_future_grid() {
    int state = 0;
    int new_state = 0;
    int order = 0;    
    for (int y = 0; y < this->width; ++y)
    {
        for (int x = 0; x < this->width; ++x)
        {
            state = present_grid[order].state;
            order = order_from_coords(x,y);
            new_state = state + this->fertility*state +
                this->mortality*pow(state,2) +
                this->migration_param*compute_diffusion_operator(x,y)*state;
            if (new_state > 0) {
                future_grid[order].state = new_state;
            } else {
                future_grid[order].state = 0;
            }
        }
    }
}

void Grid::copy_future_to_present_grid() {
    for (int y = 0; y < this->width; ++y)
    {
        for (int x = 0; x < this->width; ++x)
        {
            this->present_grid[order_from_coords(x, y)].state =
            this->future_grid[order_from_coords(x, y)].state;
        }
    }
}
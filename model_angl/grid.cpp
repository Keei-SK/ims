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
    double init_state = -1/this->mortality;
    for (int y = 0; y < this->width; ++y)
    {
        for (int x = 0; x < this->width; ++x)
        {
            // creates Cell and appends it at the end of grid
            present_grid.emplace_back(x,y,x+y);
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

void Grid::get_future_grid() {
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
                this->migration_param*diffusion_operator(x,y);
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

double Grid::diffusion_operator(int x, int y) {
    if (x > 0 && x < this->max_idx && y > 0 && y < this->max_idx) {
        return diffusion_operator_middle(x,y);
    }
    else if (x == 0 && y == 0) {
        return diffusion_operator_0();
    }
    else if (x == this->max_idx && y < this->max_idx && y > 0) {
        return diffusion_operator_x_max(y);
    }
    else if (x > 0 && x < this->max_idx && y == this->max_idx) {
        return diffusion_operator_y_max(x);
    }
    else if (x == 0 && y > 0 && y < this->max_idx) {
        return diffusion_operator_x_0(y);
    }
    else if (y == 0 && x > 0 && x < this->max_idx) {
        return diffusion_operator_y_0(x);
    }
    else if (x == this->max_idx && y == 0) {
        return diffusion_operator_x_max_y_0();
    }
    else if (y == this->max_idx && x == 0) {
        return diffusion_operator_y_max_x_0();
    } else if (x == this->max_idx && y == this->max_idx){
        return diffusion_operator_max();        
    } else {
        cout << "diffusion_operator not found!" << endl;
        cout << "x: " << x << " y: " << y << endl;
    }
    return -1.0;
}

double Grid::diffusion_operator_middle(int x, int y) {
    double diffusion_operator =
        get_present_cell(x, y-1).state +
        get_present_cell(x, y+1).state +
        get_present_cell(x+1, y).state +
        get_present_cell(x-1, y).state +
        (4*get_present_cell(x, y).state);
    return diffusion_operator;
}

double Grid::diffusion_operator_x_0(int y) {
    double diffusion_operator =
        get_present_cell(0,y-1).state +
        get_present_cell(0,y+1).state +
        get_present_cell(1,y).state +
        get_present_cell(this->max_idx,y).state +
        (4*get_present_cell(0, y).state);
    return diffusion_operator;
}

double Grid::diffusion_operator_y_0(int x) {
    double diffusion_operator =
        get_present_cell(x,this->max_idx).state +
        get_present_cell(0,1).state +
        get_present_cell(x+1,0).state +
        get_present_cell(x-1,0).state +
        (4*get_present_cell(x, 0).state);
    return diffusion_operator;
}

double Grid::diffusion_operator_0() {
    double diffusion_operator =
        get_present_cell(0,this->max_idx).state +
        get_present_cell(0,1).state +
        get_present_cell(1,0).state +
        get_present_cell(this->max_idx,0).state +
        (4*get_present_cell(0, 0).state);
    return diffusion_operator;
}

double Grid::diffusion_operator_y_max(int x) {
    double diffusion_operator =
        get_present_cell(x,this->max_idx-1).state +
        get_present_cell(x,0).state +
        get_present_cell(x+1,this->max_idx).state +
        get_present_cell(x-1,this->max_idx).state +
        (4*get_present_cell(0, 0).state);
    return diffusion_operator;
}

double Grid::diffusion_operator_x_max(int y) {
    double diffusion_operator =
        get_present_cell(this->max_idx, y-1).state +
        get_present_cell(this->max_idx, y+1).state +
        get_present_cell(0, y).state +
        get_present_cell(this->max_idx-1, y).state +
        (4*get_present_cell(this->max_idx, y).state);
    return diffusion_operator;
}

double Grid::diffusion_operator_max() {
    double diffusion_operator =
        get_present_cell(this->max_idx,this->max_idx-1).state +
        get_present_cell(0,this->max_idx).state +
        get_present_cell(0,this->max_idx).state +
        get_present_cell(this->max_idx-1,this->max_idx).state +
        (4*get_present_cell(this->max_idx, this->max_idx).state);
    return diffusion_operator;
}

double Grid::diffusion_operator_x_max_y_0() {
    double diffusion_operator =
        get_present_cell(this->max_idx, this->max_idx).state +
        get_present_cell(this->max_idx, 1).state +
        get_present_cell(0, 0).state +
        get_present_cell(this->max_idx-1, 0).state +
        (4*get_present_cell(this->max_idx, 0).state);
    return diffusion_operator;
}

double Grid::diffusion_operator_y_max_x_0() {
    double diffusion_operator =
        get_present_cell(0, this->max_idx-1).state +
        get_present_cell(0, 0).state +
        get_present_cell(1, this->max_idx).state +
        get_present_cell(this->max_idx, this->max_idx).state +
        (4*get_present_cell(0, this->max_idx).state);
    return diffusion_operator;
}
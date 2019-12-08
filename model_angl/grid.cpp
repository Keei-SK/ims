#include "grid.hpp"
#include <math.h>

void Grid::set_params(
    double reproduction_rate, double max_population, double migration_param) {
    this->fertility = (1 - reproduction_rate);
    this->mortality = (-reproduction_rate/max_population);
    //this->fertility = 
    //this->mortality = 0.5;
    this->max_population = max_population;
    this->migration_param = migration_param;
}

double Grid::random_float(double min, double max)
{
    double r = (double)rand()/(double)RAND_MAX+1.0;
    return min + r * (max - min);
}

void Grid::fill_present_grid() {
    //double init_state = -1/this->mortality;
    for (int y = 0; y < this->width; ++y)
    {
        for (int x = 0; x < this->width; ++x)
        {
            // creates Cell and appends it at the end of grid
            this->present_grid.emplace_back(x,y,0);
        }
    }
    for (int y = 3; y < 8; ++y)
    {
        for (int x = 3; x < 9; ++x)
        {
            // creates Cell and appends it at the end of grid
            this->present_grid[order_from_coords(x, y)].state = random_float(0, 0.2);
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
    return x + (y*this->width);
}

void Grid::print_present_grid() {
    for (int y = 0; y < this->width; ++y)
    {
        for (int x = 0; x < this->width; ++x)
        {
            printf("%.02f ", this->present_grid[order_from_coords(x, y)].state);
        }
        cout << endl;
    }
    cout << endl;
}

void Grid::get_future_grid(int month) {
    double state = 0;
    double new_state = 0;
    int order = 0;
    double winter_coef;


    for (int y = 0; y < this->width; ++y)
    {
        for (int x = 0; x < this->width; ++x)
        {
            order = order_from_coords(x,y);
            state = present_grid[order].state;
            
            if (month > 7) { //zima - populace zacina umirat
                new_state = state +
                this->mortality*pow(state,2) +
                this->migration_param*diffusion_operator(x,y);

                int winter_intensity = (int) (1 + 3 * (rand() / RAND_MAX+1.0));
                if (winter_intensity == 1){ //weak winter
                    winter_coef = 0.82;
                }
                else if(winter_intensity == 2){ //medium strong winter
                    winter_coef = 0.75;
                }
                else{ // strong winter
                    winter_coef = 0.68;
                }
                new_state *= winter_coef;
            }
            else if (month >= 7) {
                new_state = state +
                this->mortality*pow(state,2) +
                this->migration_param*diffusion_operator(x,y);
            }
            else {
                new_state = state + this->fertility*state +
                this->mortality*pow(state,2) +
                this->migration_param*diffusion_operator(x,y);
            }
             
            if (new_state < 0) {
                new_state = 0;
            }
            future_grid[order].state = new_state;
        }
    }
}

void Grid::show_in_terminal()
{
    for(int y = 0; y < this->width; y++)
    {
        for (int x = 0; x < this->width; x++)
        {
            if(this->present_grid[order_from_coords(x, y)].state < 0.1)
            {
                cout << "\033[1;30m 0\033[0m ";
            }
            else if (this->present_grid[order_from_coords(x, y)].state < 0.2)
            {
                cout << "\033[1;35m 1\033[0m ";
            }
            else if (this->present_grid[order_from_coords(x, y)].state < 0.3)
            {
                cout << "\033[1;32m 2\033[0m ";
            }
            else if (this->present_grid[order_from_coords(x, y)].state < 0.4)
            {
                cout << "\033[1;33m 3\033[0m ";
            }
            else if (this->present_grid[order_from_coords(x, y)].state < 0.5)
            {
                cout << "\033[1;34m 4\033[0m ";
            }
            else
            {
                cout << "\033[1;31m 5\033[0m ";
            }
        }
        cout << endl;
    }
    cout << endl;
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

double Grid::get_average() {
    double sum = 0.0;
    for (int y = 0; y < this->width; ++y)
    {
        for (int x = 0; x < this->width; ++x)
        {
            sum += this->present_grid[order_from_coords(x, y)].state;
        }
    }
    double area = this->width*this->width;
    return sum/area;
}

double Grid::diffusion_operator(int x, int y) {
    double diffusion_operator = 0.0;
    unsigned int count = 0;
    
    if (x > 0) {
        diffusion_operator += get_present_cell(x-1, y).state;
        count++;
    }
    
    if (x < this->max_idx) {
        diffusion_operator += get_present_cell(x+1, y).state;
        count++;
    }
    
    if (y > 0) {
        diffusion_operator += get_present_cell(x, y-1).state;
        count++;
    }
    
    if (y < this->max_idx) {
        count++;
        diffusion_operator += get_present_cell(x, y+1).state;
    }

    diffusion_operator -= (count*get_present_cell(x, y).state);
    return diffusion_operator;
}

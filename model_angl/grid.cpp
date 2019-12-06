#include "grid.hpp"

void Grid::fill_present_grid() {
    for (int y = 0; y < this->width; ++y)
    {
        for (int x = 0; x < this->width; ++x)
        {
            // creates Cell and appends it at the end of grid
            present_grid.emplace_back(x,y,0);
        }
    }
}

int Grid::order_from_coords(int x, int y) {
    return y + (x*this->width);
}

void Grid::print_present_grid() {
    for (int y = 0; y < this->width; ++y)
    {
        for (int x = 0; x < this->width; ++x)
        {
            cout << present_grid[order_from_coords(x, y)].density << " ";
        }
        cout << endl;
    }
}
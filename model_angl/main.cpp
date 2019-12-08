#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

using namespace std;

#include "cell.hpp"
#include "grid.hpp"
#include "image.hpp"

//int argc, char* argv[]

void display();

int main()
{
    srand(time(NULL));
    Grid grid(100);

    int sim_months = 48;
    // reproduction_rate,  max_population, migration_pararameter
    grid.set_params(0.85, 5000, 0.2);
    grid.init_present_grid();
    int month = 0;
    Image image(600, 600);
    for (int t = 0; t < sim_months; ++t)
    {
        month = t % 12;
        grid.get_future_grid(month);
        grid.copy_future_to_present_grid();
        image.create_image(grid, 1000, month, true);
    }

    return 0;
}


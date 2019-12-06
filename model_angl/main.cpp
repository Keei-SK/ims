#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#include "cell.hpp"
#include "grid.hpp"

int main(int argc, char* argv[])
{   
    Grid grid(5);
    grid.set_params(1.2, 100, 0.2);
    grid.fill_present_grid();
    grid.print_present_grid();
    for (int i = 0; i < 10; ++i)
    {    
        grid.compute_future_grid();
        grid.copy_future_to_present_grid();
        grid.print_present_grid();
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#include "cell.hpp"
#include "grid.hpp"
//int argc, char* argv[]
int main()
{   
    Grid grid(10);

    // reproduction_rate,  max_population, migration_pararameter
    grid.set_params(0.99, 100, 0.05);
    cout << "fert: " << grid.fertility << " mort: " << grid.mortality << endl;
    grid.fill_present_grid();
    grid.print_present_grid();

    int month = 0;
    for (int i = 0; i < 48; ++i)
    {    
        month = i % 12;
        grid.get_future_grid(month);
        grid.copy_future_to_present_grid();
        grid.print_present_grid();
        //cout << grid.get_average() << endl;
    }
    return 0;
}
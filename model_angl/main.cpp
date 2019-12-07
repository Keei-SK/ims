#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#include "cell.hpp"
#include "grid.hpp"
//int argc, char* argv[]
int main()
{   
    Grid grid(50);

    // reproduction_rate,  max_population, migration_pararameter
    grid.set_params(0.99, 100, 0.2);
    cout << "fert: " << grid.fertility << " mort: " << grid.mortality << endl;
    grid.fill_present_grid();
    grid.print_present_grid();
    for (int i = 0; i < 10; ++i)
    {    
        grid.get_future_grid();
        grid.copy_future_to_present_grid();
        grid.print_present_grid();
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#include "cell.hpp"
#include "grid.hpp"

int main(int argc, char* argv[])
{   
    Grid grid(5);
    grid.fill_present_grid();
    grid.print_present_grid();
    return 0;
}
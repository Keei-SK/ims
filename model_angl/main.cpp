#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#include "cell.hpp"
#include "grid.hpp"

int main(int argc, char* argv[])
{   
    Cell cell(20, 2 ,20);
    cout << cell.x << endl;
    return 0;
}
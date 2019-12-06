//
//  Cell.hpp
//  ims-ca
//
//  Created by Pavel Witassek on 04/12/2018.
//  Copyright © 2018 Pavel Witassek. All rights reserved.
//

#ifndef Cell_hpp
#define Cell_hpp

#include <iostream>
#include <climits>
#include <vector>
#include <cmath>

enum CellState { wall, empty, person, obstacle, door, doorPerson };

class Cell {
private:
    CellState state;
    unsigned long x, y;
    std::vector<double> exitDistances;
    double sumOfexitDistances;
    
    
public:
    Cell(unsigned long x, unsigned long y, CellState state);
    unsigned long getX();
    unsigned long getY();
    CellState getState();
    void setNewState(CellState state);
    double getDistance(unsigned int exitIndex);
    void setDistance(unsigned int exitIndex, double distance);
    double getSumOfexitDistances();
    
    int exitIndex;

};

#endif /* Cell_hpp */

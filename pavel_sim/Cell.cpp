//
//  Cell.cpp
//  ims-ca
//
//  Created by Pavel Witassek on 04/12/2018.
//  Copyright © 2018 Pavel Witassek. All rights reserved.
//

#include "Cell.hpp"

Cell::Cell(unsigned long x, unsigned long y, CellState state) {
    this->x = x;
    this->y = y;
    this->state = state;
}

CellState Cell::getState() {
    return this->state;
}

void Cell::setNewState(CellState state) {
    this->state = state;
}

void Cell::setDistance(unsigned int exitIndex, double distance) {
    std::vector<double>::iterator it;
    unsigned int i = 0;
    for (it = this->exitDistances.begin(); it != this->exitDistances.end(); it++) {
        if (i == exitIndex) {
            break;
        }
        i++;
    }
    
    if (exitIndex >= this->exitDistances.size() || this->exitDistances.size() <= 0) {
        this->exitDistances.insert(it, distance); //round(distance*1000.0 )/1000.0);
    } else {
        *it = distance;
        //*it = round(distance*1000.0 )/1000.0;
    }
    
    this->sumOfexitDistances = 0;
    for (it = this->exitDistances.begin(); it != this->exitDistances.end(); it++) {
        this->sumOfexitDistances += *it;
    }
}

double Cell::getDistance(unsigned int exitIndex) {
    if (this->getState() == door) {
        return 0.0;
    } else if (this->getState() == obstacle || this->getState() == wall) {
        return -1.0;
    }
    return this->exitDistances.at(exitIndex);
}

unsigned long Cell::getX() {
    return this->x;
}

unsigned long Cell::getY() {
    return this->y;
}

double Cell::getSumOfexitDistances() {
    return this->sumOfexitDistances;
}

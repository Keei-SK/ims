#ifndef CELL_HPP
#define CELL_HPP

class Cell {
public:
    void updateDensity(int density);
    void setCell(int x, int y, int density);
    Cell(int x, int y, int density) {
        setCell(x, y, density);
    };    
    int density;
    int x;
    int y;
};

#endif
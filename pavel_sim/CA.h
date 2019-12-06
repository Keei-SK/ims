#ifndef CA_CA_H
#define CA_CA_H

#include <vector>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <ctime>
#include <cmath>

#include "Cell.hpp"
#include "Image.h"

#define TIME_STEP 0.40

using namespace std;
using namespace cv;


class CA {
public:
    CA();
    void run();
    vector<vector<Cell*>> getCurrentState();
    double getTime();
    void generateNewState();
    int getPersonCellCount();
    bool init(string filename);
    bool graphics;

    ~CA();
private:
    vector<vector<Cell*>> currentState;
    vector<vector<Cell*>> nextState;
    vector<Cell*> exitCells;
    int personCellCount;
    double modelTime;
    double alpha;

    unsigned long width;
    unsigned long height;

    Image *image;

    Cell* getSmallestDistanceCell(list<Cell*> *unvisitedCels, unsigned int exitIndex);
    void calculateDistance();
    void copyState(vector<vector<Cell*>> *source, vector<vector<Cell*>> *destination);
    bool isMoved(list<Cell *> *moved, Cell* currentCell);
    Cell* selectCellToMove(list<Cell*> *people);
    Cell* randomCell(list<Cell*> *cellsList);
    void initExitCells();
    void calculateEuclidDistance();
};


#endif //CA_CA_H

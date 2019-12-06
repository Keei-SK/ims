#include "CA.h"

CA::CA(){
    this->modelTime = 0.0;
    this->personCellCount = 0;
    this->alpha = 0.0;
    this->graphics = false;
    srand(time(nullptr));
}


bool CA::init(string filename) {
    fstream fileBuf;
    string line;
    char delimiter = ' ';

    fileBuf.open(filename, fstream::in);
    if(fileBuf.fail()){
        cerr << "Chyba: soubor "<<filename<<" se nepodarilo otevrit"<<endl;
        this->graphics = false;
        return false;
    }

    if(!getline(fileBuf, line, delimiter)){
        cerr << "Chyba v souboru."<<endl;
        this->graphics = false;
        return false;
    }
    this->height = stoul(line);

    if(!getline(fileBuf, line, delimiter)){
        cerr << "Chyba v souboru."<<endl;
        this->graphics = false;
        return false;
    }
    this->width = stoul(line);

    if(!getline(fileBuf, line)){
        cerr << "Chyba v souboru."<<endl;
        this->graphics = false;
        return false;
    }
    this->alpha = stod(line);

    int cellValue;
    this->currentState.resize(this->height);
    this->nextState.resize(this->height);
    for(unsigned long rows = 0; rows < this->height; rows++){
        this->currentState[rows].resize(this->width);
        this->nextState[rows].resize(this->width);
        if(!getline(fileBuf, line)){
            cerr << "Chyba v souboru."<<endl;
            this->graphics = false;
            return false;
        }
        for(unsigned long cols = 0; cols < this->width; cols++){

            cellValue = line[cols] - '0';

            switch (cellValue){
                case 1:
                    this->currentState[rows][cols] = new Cell(rows, cols, wall);
                    this->nextState[rows][cols] = new Cell(rows, cols, wall);
                    break;

                case 2:
                    this->currentState[rows][cols] = new Cell(rows, cols, obstacle);
                    this->nextState[rows][cols] = new Cell(rows, cols, obstacle);
                    break;

                case 3:
                    this->currentState[rows][cols] = new Cell(rows, cols, person);
                    this->nextState[rows][cols] = new Cell(rows, cols, person);
                    this->personCellCount++;
                    break;
                    
                case 4:
                    this->currentState[rows][cols] = new Cell(rows, cols, door);
                    this->nextState[rows][cols] = new Cell(rows, cols, door);
                    this->exitCells.push_back(this->currentState[rows][cols]);
                    break;

                default:
                    this->currentState[rows][cols] = new Cell(rows, cols, empty);
                    this->nextState[rows][cols] = new Cell(rows, cols, empty);
                    break;
            }
        }
    }

    if(!fileBuf.is_open()) {
        cerr << "Chyba: soubor "<<filename<<" se nepodarilo uzavrit"<<endl;
        this->graphics = false;
        return false;
    }
    fileBuf.close();
    
    //calculateDistance();
    calculateEuclidDistance();

    if (this->graphics) {
        this->image = new Image(this->width, this->height);
        this->image->createImage(this->getCurrentState(), this->getTime(), 5000, true);
    }
    cout << "Počet osob: "+to_string(this->personCellCount)<<endl;
    return true;

}


void CA::run() {
    while(this->personCellCount > 0){
        this->modelTime+=TIME_STEP;
        CA::generateNewState();
        if (this->graphics) {
            this->image->createImage(this->getCurrentState(), this->getTime(), 50, true);
        }
    }
    cout << "Čas evakuace: "+to_string(this->modelTime)<<endl;
}

void CA::generateNewState() {
    copyState(&this->currentState, &this->nextState);
    list<Cell*> unvisitedPersonCells;
    list<Cell*> allPersonCells;
    list<Cell*>::iterator personIt;
    Cell *currentCell = nullptr;
    for(unsigned long rows = 0; rows < this->height; rows++) {
        for (unsigned long cols = 0; cols < this->width; cols++) {
            currentCell = this->currentState[rows][cols];
            if (currentCell->getState() == person) {
                unvisitedPersonCells.push_back(currentCell);
                allPersonCells.push_back(currentCell);
            } else if (currentCell->getState() == doorPerson) {
                this->nextState[currentCell->getX()][currentCell->getY()]->setNewState(door);
                this->personCellCount--;
            }
        }
    }
    
    list<Cell*> movedPeople;
    unsigned long rows = 0;
    unsigned long cols = 0;
    int random = (int)rand() % this->height*this->width;
    int counter = 0;
    while ((currentCell = randomCell(&unvisitedPersonCells)) != nullptr && counter < random) {
        if (this->exitCells.size() <= 0) {
            break;
        }
        counter++;
        rows = currentCell->getX();
        cols = currentCell->getY();
        unvisitedPersonCells.remove(currentCell);
        
        Cell *currentCell = this->currentState[rows][cols];
        Cell *nextCell = this->nextState[rows][cols];
        
        // calculate target exit probabilities (Ei)
        // Ei = (1-A)*p_1 + A*p_2
        // p_1 = (D^i_xy)/SUM(D^i_xy)
        // p_2 = 1 - (N^i_k)/N_sum
        unsigned int sumOfProbilities = 0;
        for (int exitIndex = 0; exitIndex < this->exitCells.size(); exitIndex++) {
            sumOfProbilities += currentCell->getSumOfexitDistances()-currentCell->getDistance(exitIndex);
        }
        
        vector<double> eiProbabilities;
        for (int exitIndex = 0; exitIndex < this->exitCells.size(); exitIndex++) {
            double p1 = (double)(currentCell->getSumOfexitDistances()-currentCell->getDistance(exitIndex))/sumOfProbilities;
            unsigned int countOfNearerPersons = 0;
            if (this->alpha > 0) {
                for (personIt = allPersonCells.begin(); personIt != allPersonCells.end(); personIt++) {
                    if (currentCell->getDistance(exitIndex) > (*personIt)->getDistance(exitIndex)+2) {
                        countOfNearerPersons++;
                    }
                }
            }
            double p2 = 1 - countOfNearerPersons/(double)this->personCellCount;
            double ei = (1-this->alpha)*p1 + this->alpha*p2;
            eiProbabilities.push_back(ei);
        }
        
        // correct pstr of multiple cells exit
        for (int exitIndex = 0; exitIndex < this->exitCells.size() && this->exitCells.size() > 1; exitIndex++) {
            Cell *tmp = this->exitCells.at(exitIndex);
            if (tmp->getX() < this->height && tmp->getX() > 0) {
                if (this->currentState[tmp->getX()-1][tmp->getY()]->getState() == door) {
                    eiProbabilities.at(exitIndex) += eiProbabilities.at(this->currentState[tmp->getX()-1][tmp->getY()]->exitIndex);
                    eiProbabilities.at(this->currentState[tmp->getX()-1][tmp->getY()]->exitIndex) = 0;
                }
            }
            if (tmp->getY() < this->width-1) {
                if (this->currentState[tmp->getX()][tmp->getY()+1]->getState() == door) {
                    eiProbabilities.at(exitIndex) += eiProbabilities.at(this->currentState[tmp->getX()][tmp->getY()+1]->exitIndex);
                    eiProbabilities.at(this->currentState[tmp->getX()][tmp->getY()+1]->exitIndex) = 0;
                }
            }
        }
        
        unsigned int selectExitIndex = (unsigned int)eiProbabilities.size()-1;
        //double probability = (double)rand() / RAND_MAX;
        double tmp = 0.0;
        for (int exitIndex = 0; exitIndex < this->exitCells.size(); exitIndex++) {
            if (tmp < eiProbabilities.at(exitIndex)) {
                selectExitIndex = exitIndex;
                tmp = eiProbabilities.at(exitIndex);
            }
        }
        
        // find empty neighbours
        list<Cell*> emptyDoorCells;
        list<Cell*> emptyNeighboursCells;
        double minLxy = INT_MAX+0.0;
        for (short i = -1; i <= 1; i++) {
            for (short j = -1; j <= 1; j++) {
                long row = rows+i;
                long col = cols+j;
                if (row < 0 || col < 0) {
                    continue;
                } else if (row >= this->height || col >= this->width) {
                    continue;
                }
                if (currentCell != this->currentState[row][col] && ((this->currentState[row][col]->getState() == empty && this->nextState[row][col]->getState() == empty) || this->currentState[row][col]->getState() == person)) {
                    emptyNeighboursCells.push_back(this->currentState[row][col]);
                    if (this->currentState[row][col]->getDistance(selectExitIndex) < minLxy) {
                        minLxy = this->currentState[row][col]->getDistance(selectExitIndex);
                    }
                } else if (currentCell != this->currentState[row][col] && this->currentState[row][col]->getState() == door && this->nextState[row][col]->getState() == door) {
                    emptyDoorCells.push_back(this->currentState[row][col]);
                }
            }
        }
        
        list<Cell*>::iterator it;
        double sumMxy = 0.0;
        for (it = emptyNeighboursCells.begin(); it != emptyNeighboursCells.end(); it++) {
            sumMxy += (minLxy/(*it)->getDistance(selectExitIndex));
        }
        
        
        // calculate neighbours probabilities (Pxy)
        double maxPxy = 0.0;
        Cell *bestCell = nullptr;
        double currentPxy = 0.0;
        bool correctEmpty = false;
        for (it = emptyNeighboursCells.begin(); it != emptyNeighboursCells.end() && sumMxy > 0; it++) {
            currentPxy = (minLxy/(double)(*it)->getDistance(selectExitIndex))/sumMxy;
            if ((*it)->getState() == person && random < (this->height*this->width)/10) {
                currentPxy = 0.0;
            }
            if (maxPxy < currentPxy) {
                bestCell = *it;
                maxPxy = currentPxy;
            }
        }
        
        
        if (emptyDoorCells.size() > 0) {
            for (it = emptyDoorCells.begin(); it != emptyDoorCells.end(); it++) {
                if (this->nextState[(emptyDoorCells.front())->getX()][(emptyDoorCells.front())->getY()]->getState() == door) {
                    nextCell->setNewState(empty);
                    this->nextState[(emptyDoorCells.front())->getX()][(emptyDoorCells.front())->getY()]->setNewState(doorPerson);
                    break;
                }
            }
        } else if (bestCell != nullptr && bestCell->getState() == empty) {
            nextCell->setNewState(empty);
            this->nextState[bestCell->getX()][bestCell->getY()]->setNewState(person);
        }
    }
    copyState(&this->nextState, &this->currentState);
}

Cell* CA::randomCell(list<Cell*> *cellsList) {
    if (cellsList->size() <= 0) {
        return nullptr;
    }
    
    int random = (rand() % cellsList->size());
    list<Cell*>::iterator it;
    unsigned int i = 0;
    for (it = cellsList->begin(); it != cellsList->end(); it++) {
        if(i >= random) {
            return *it;
        }
        i++;
    }
    
    return nullptr;
}

vector<vector<Cell*>> CA::getCurrentState() {
    return this->currentState;
}

double CA::getTime() {
    return this->modelTime;
}

int CA::getPersonCellCount() {
    return this->personCellCount;
}

Cell* CA::getSmallestDistanceCell(list<Cell*> *unvisitedCels, unsigned int exitIndex) {
    if (unvisitedCels->size() <= 0) {
        return nullptr;
    }
    
    Cell *smallestDistanceCell = unvisitedCels->front();
    list<Cell*>::iterator it;
    for (it = unvisitedCels->begin(); it != unvisitedCels->end(); it++) {
        if((*it)->getDistance(exitIndex) < smallestDistanceCell->getDistance(exitIndex)) {
            smallestDistanceCell = *it;
        }
    }
    
    return smallestDistanceCell;
}

void CA::initExitCells() {
    vector<Cell*>::iterator it;
    unsigned int i = 0;
    for (it = this->exitCells.begin(); it != this->exitCells.end(); it++) {
        (*it)->setDistance(i, 0);
        (*it)->exitIndex = i;
        i++;
    }
}

void CA::calculateEuclidDistance() {
    this->initExitCells();
    
    Cell *currentCell = nullptr;
    vector<Cell*>::iterator it;
    unsigned int i = 0;
    for(unsigned long rows = 0; rows < this->height; rows++) {
        for (unsigned long cols = 0; cols < this->width; cols++) {
            currentCell = this->currentState[rows][cols];
            for (it = exitCells.begin(); it != exitCells.end(); it++) {
                if (currentCell->getState() == empty || currentCell->getState() == person) {
                    int deltaY = (int)(currentCell->getY() - (*it)->getY());
                    int deltaX = (int)(currentCell->getX() - (*it)->getX());
                    currentCell->setDistance(i, sqrt(deltaX*deltaX+deltaY*deltaY));
                } else if (currentCell->getState() == obstacle || currentCell->getState() == wall) {
                    currentCell->setDistance(i, -1.0);
                }
                i++;
            }
            i = 0;
        }
    }
}

void CA::calculateDistance() {
    this->initExitCells();
    
    Cell *currentCell = nullptr;
    for(unsigned long rows = 0; rows < this->height; rows++) {
        for (unsigned long cols = 0; cols < this->width; cols++) {
            currentCell = this->currentState[rows][cols];
            for (int i = 0; i < exitCells.size(); i++) {
                if (currentCell->getState() == empty || currentCell->getState() == person) {
                    currentCell->setDistance(i, INT_MAX);
                } else if (currentCell->getState() == obstacle || currentCell->getState() == wall) {
                    currentCell->setDistance(i, -1);
                }
            }
        }
    }
    
    list<Cell*> unvisitedCels;
    for (int exitIndex = 0; exitIndex < exitCells.size(); exitIndex++) {
        unvisitedCels.clear();
        
        for(unsigned long rows = 0; rows < this->height; rows++) {
            for (unsigned long cols = 0; cols < this->width; cols++) {
                currentCell = this->currentState[rows][cols];
                if (currentCell->getState() == empty || currentCell->getState() == person || (currentCell->getState() == door && exitIndex == currentCell->exitIndex)) {
                    unvisitedCels.push_back(currentCell);
                }
            }
        }
    
        currentCell = getSmallestDistanceCell(&unvisitedCels, exitIndex);
        Cell *neighbours[8];
        int x = 0;
        while(unvisitedCels.size() > 0 && currentCell != nullptr) {
            unsigned long rows = currentCell->getX();
            unsigned long cols = currentCell->getY();
            // find neighbours
            for (short i = -1; i <= 1; i++) {
                for (short j = -1; j <= 1; j++) {
                    long row = rows+i;
                    long col = cols+j;
                    if (row < 0 || col < 0) {
                        continue;
                    } else if (row >= this->height || col >= this->width) {
                        continue;
                    }
                    if (currentCell != this->currentState[row][col] && (this->currentState[row][col]->getState() == empty || this->currentState[row][col]->getState() == person)) {
                        neighbours[x] = this->currentState[row][col];
                        x++;
                    }
                }
                
            }
            // update distance
            for (int i = 0; i < x; i++) {
                if (neighbours[i]->getDistance(exitIndex) > currentCell->getDistance(exitIndex)) {
                    neighbours[i]->setDistance(exitIndex, currentCell->getDistance(exitIndex)+1);
                }
            }
            
            // mark current cell as visited
            unvisitedCels.remove(currentCell);
            
            // find shortest distance in unvisitedCells
            currentCell = getSmallestDistanceCell(&unvisitedCels, exitIndex);
            x = 0;
        }
    }
}

void CA::copyState(vector<vector<Cell*>> *source, vector<vector<Cell*>> *destination) {
    Cell* tmpCell = nullptr;
    for(unsigned long rows = 0; rows < this->height; rows++){
        for (unsigned long cols = 0; cols < this->width; cols++) {
            tmpCell = (*source)[rows][cols];
            (*destination)[rows][cols]->setNewState(tmpCell->getState());
        }
    }
}

CA::~CA() {
    if (this->graphics) {
        delete this->image;
    }
}

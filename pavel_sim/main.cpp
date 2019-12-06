#include <iostream>

#include "CA.h"

using namespace std;

int main(int argc, const char *argv[]) {
    if(argc < 2){
        cerr << "Prvni parametr musi byt cesta souboru s experimentem."<<endl;
        exit(EXIT_FAILURE);
    }

    CA *ca = new CA();
    if (argc > 2 && strcmp(argv[2],"true") == 0) {
        ca->graphics = true;
    }
    if(ca->init(argv[1])) {
        ca->run();
    }
    delete ca;
    exit(EXIT_SUCCESS);
}

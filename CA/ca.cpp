#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <unistd.h>

#define ERR_ARG 1
using namespace std;

typedef struct
{
    uint32_t h;
    uint32_t o;
    uint32_t j;
    uint32_t p;
}Arguments;

int parse_args(int argc ,char *argv[]);
int used_twice(int param);
void print_usage();

Arguments args;

int main(int argc, char* argv[]) {
    int err = parse_args(argc, argv);
}

void print_wrong_range(char arg) {
    cout << arg << " spatny rozsah" << endl;
}

// Parses command line arguments and save them to global Arguments structure
int parse_args(int argc ,char *argv[])
{   
    int opt;
    int h = 0;
    int o = 0;
    int j = 0;
    int p = 0;


    while ((opt = getopt(argc, argv, "h:o:j:p:")) != -1) {        
        switch(opt) {
            case 'h':
                if (used_twice(h)) return ERR_ARG;
                args.h = atoi(optarg);
                if (args.h < 1 || args.h > 10000) {
                    print_wrong_range('h');
                    return ERR_ARG;
                }
                break;
            case 'o':
                if (used_twice(o)) return ERR_ARG;
                args.o = atoi(optarg);
                if (args.o < 1 || args.o > 4) {
                    print_wrong_range('o');
                    return ERR_ARG;
                }
                break;
            case 'j':                
                if (used_twice(j)) return ERR_ARG;
                args.j = atoi(optarg);
                if (args.j < 1 || args.j > 3) {
                    print_wrong_range('j');
                    return ERR_ARG;
                }
                break;
            case 'p':
                if (used_twice(p)) return ERR_ARG;
                for (unsigned int i = 0; i < strlen(optarg); i++)
                {
                   if (!isdigit(optarg[i])) {
                        fprintf(stderr, "Timeout has to be a number\n");
                        return ERR_ARG;
                    } 
                }
                args.p = atoi(optarg);
                if (args.p < 1 || args.p > 4) {
                    print_wrong_range('p');
                    return ERR_ARG;
                }
                break;
            default:
                print_usage();
                return ERR_ARG;
        }
    }
    // check if there is an unknown argument
    if (argc != 9) {
        print_usage();
        return ERR_ARG;
    }

    return 0;
}

// prints usage message
// TODO
void print_usage() {
    fprintf(stderr, "Error wrong arguments\n");
    fprintf(stderr, "Usage: -h [1-10000] -o [1-4] -j [1-3] -p[1-5]\n");
}

// Ensures that each parameter is used only once
int used_twice(int param) {
    if (param) {
        fprintf(stderr, "Each parameter can be used only once.\n");
        return ERR_ARG;
    }
    return 0;
}
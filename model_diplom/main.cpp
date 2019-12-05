#include "args.h"
#include <math.h>
#define ERR_ARG 1
using namespace std;

#define MAX_AGE 14
#define MONTHS 30

class Model {
public:
    Model(Arguments args);
    Arguments param;
    int newborn_females = 0; //n0(t+1)    
    double beta0 = 0; //bi(t) - female of age i has in month t, bi daughters
    double beta1 = 0;
    int all_females = 200;
    int females_of_age[MAX_AGE+1];
    int num_daughters_in_month = 0;
    double p = 0.99;

    int get_num_daughters_in_month();
    int get_newborn_females();
    void update_females_sum();
    void simulate();
    int get_all_females();
    double getBeta0();
};

Model::Model(Arguments args) {
    param = args;
    cout << param.max_daughters_month << endl;
    cout << "init" << endl;
    for (int i = 0; i <= MAX_AGE; ++i)
    {
        females_of_age[i] = 2;
    }
    beta0 = log(p/(1-p));
    beta1 = -(log((2-p)/(1-p))/1000);
}

void Model::simulate(){
    cout << get_newborn_females() << endl;
}

int Model::get_all_females() {
    int sum = 0;
    for (int i = 0; i <= MAX_AGE; i++)
    {
        sum += females_of_age[i];
    }
    all_females = sum;
    return all_females;
}

// bi(t)
int Model::get_num_daughters_in_month() {
    double power_e = pow(M_E,(beta0+beta1*get_all_females()));
    num_daughters_in_month = param.max_daughters_month*(power_e/(1+power_e));
    return num_daughters_in_month;
}

// n0(t+1)
int Model::get_newborn_females() {
    cout << "calc_newborn_females" << endl;
    get_num_daughters_in_month();
    int sum = 0;
    for (int i = 0; i <= MAX_AGE-4; i++)
    {
        sum += num_daughters_in_month*females_of_age[i];
    }
    newborn_females = sum;
    return newborn_females;
}

int main(int argc, char* argv[]) {
    Arguments args;
    int err = parse_args(&args, argc, argv);
    Model myModel(args);
    myModel.simulate();
}

void print_args(Arguments args) {
    cout << args.max_daughters_month << " " << args.dens_b_half << " " << args.dens_b_half << " " <<
    args.norm_age_repro << " " << args.max_age_repro << " " << args.dens_repro_delayed << " " <<
    args.min_surv << " " << args.max_surv << " " << args.mother_age_repro << " " << args.max_age << endl;
}

// Parses command line arguments and save them to global Arguments structure
int parse_args(Arguments *args, int argc ,char *argv[])
{   
    int opt;
    bool B = false;
    bool t = false;
    bool l = false;
    bool L = false;
    bool c = false;
    bool s = false;
    bool S = false;
    bool A = false;
    bool k = false;

    while ((opt = getopt(argc, argv, "B:t:l:L:c:s:S:A:k:")) != -1) { 
    // -t 1000 -l 1 -L 10 -c 500 -s 0.25 -S 0.95 -A 10 -k 14       
        switch(opt) {
            case 'B':
                if (used_twice(B)) return ERR_ARG;
                args->max_daughters_month = atof(optarg);
                B = true;
                break;
            case 't':
                if (used_twice(t)) return ERR_ARG;
                args->dens_b_half = atoi(optarg);
                t = true;
                break;
            case 'l':                
                if (used_twice(l)) return ERR_ARG;
                args->norm_age_repro = atoi(optarg);
                l = true;
                break;            
            case 'L':
                if (used_twice(L)) return ERR_ARG;
                args->max_age_repro = atoi(optarg);
                L = true;
                break;
            case 'c':
                if (used_twice(c)) return ERR_ARG;
                args->dens_repro_delayed = atoi(optarg);
                c = true;
                break;            
            case 's':
                if (used_twice(s)) return ERR_ARG;
                args->min_surv = atof(optarg);
                s = true;
                break;            
            case 'S':
                if (used_twice(S)) return ERR_ARG;
                args->max_surv = atof(optarg);
                S = true;
                break;
            case 'A':
                if (used_twice(A)) return ERR_ARG;
                args->mother_age_repro = atoi(optarg);
                A = true;
                break;
            case 'k':
                if (used_twice(k)) return ERR_ARG;
                args->max_age = atoi(optarg);
                k = true;
                break;
            default:
                print_usage();
                return ERR_ARG;
        }
    }
    // check if there is an unknown argument
    /*if (argc != 9) {
        print_usage();
        return ERR_ARG;
    }*/

    return 0;
}

// prints usage message
// TODO
void print_usage() {
    fprintf(stderr, "Error wrong arguments\n");
    fprintf(stderr, "Usage:...\n");
}

// Ensures that each parameter is used only once
int used_twice(int param) {
    if (param) {
        fprintf(stderr, "Each parameter can be used only once.\n");
        return ERR_ARG;
    }
    return 0;
}
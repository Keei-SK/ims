#include "args.h"
#include <math.h>
#define ERR_ARG 1
using namespace std;

#define MAX_AGE 14
#define MONTHS 30

class Model {
public:
    Model(Arguments args);
    void simulate();

private:
    Arguments param;
    double newborn_females = 0; //n0(t+1)    
    double beta0 = 0;
    double beta1 = 0;
    double gamma0 = 0;
    double gamma1 = 0;
    double all_females = 0;         //N(t)
    double females_of_age[MAX_AGE+1]; //ni(t)
    double coef_surv[MAX_AGE+1]  = {0.95, 0.93, 0.90, 0.88, 0.86, 0.85, 0.82, 0.78, 0.75, 0.60, 0.50, 0.40, 0.30, 0.27, 0.25};
    double num_daughters_in_month = 0;
    double p = 0.99;
    double max_min = 0;
    int order = 0;

    double get_num_daughters_in_month();
    double get_newborn_females();
    
    double get_all_females();
    double get_females_of_age();
    double get_newborn_females_cnt_per_age(int age);
    //double get_coef_surv();
    double get_gamma_function_result(int age);
    double new_num_females_of_age();
};

Model::Model(Arguments args) {
    param = args;
    for (int i = 0; i <= MAX_AGE; ++i)
    {
        females_of_age[i] = i;
    }
    beta0 = log(p/(1-p));
    if (param.dens_b_half != 0) {
        beta1 = -(log((2-p)/(1-p)))/param.dens_b_half;
    } else {
        beta1 = 0;
    }

    max_min = param.max_surv - param.min_surv;
    gamma0 = log(p/(1-p));
    if (param.mother_age_repro != 0) {
        gamma1 = -(log(2-p))/param.mother_age_repro;
    } else {
        gamma1 = 0;
    }
}

void Model::simulate() {
    double dens_repro_delayed = 0;
    for (int i = 0; i < 100; ++i)
    {
        int month = i % 12;

        cout << get_all_females() << endl;
        new_num_females_of_age();
        if (month >= 0 && month < 8) {
            females_of_age[0] = get_newborn_females();
        }        
    }    

    //get_coef_surv();
    /*cout << "num_daughters_in_month " << num_daughters_in_month << endl;
    cout << "newborn_females " << newborn_females << endl;*/
}

// N(t)
double Model::get_all_females() {
    double sum = 0;
    for (int i = 0; i <= MAX_AGE; i++)
    {
        sum += females_of_age[i];
    }
    all_females = sum;
    return all_females;
}

// bi(t)
double Model::get_num_daughters_in_month() {
    get_all_females();
    double power_e = pow(M_E,(beta0+beta1*all_females));
    /*cout << "beta1:" << beta1 << endl;
    cout << "power_e " << power_e << endl;
    cout << "pow: " << param.max_daughters_month*(double)(power_e/(1+power_e)) << endl;*/
    num_daughters_in_month = param.max_daughters_month*(double)(power_e/(1+power_e));
    return num_daughters_in_month;
}

// n0(t+1)
double Model::get_newborn_females() {
    get_num_daughters_in_month();
    double sum = 0;
    for (int i = 0; i <= MAX_AGE-4; i++)
    {
        sum += num_daughters_in_month*females_of_age[i];
    }
    newborn_females = sum;
    return newborn_females;
}
// wi(t)
double Model::get_newborn_females_cnt_per_age(int age) {
    if (newborn_females != 0) {
        return (num_daughters_in_month*females_of_age[age])/females_of_age[0];
    }
    return 0;
}

/*// complicated formula at the end of s0(t+1)
double Model::get_gamma_function_result(int age) {
    cout << "females of age: " << females_of_age[age] << endl;
    double numerator = pow(M_E,gamma0 +(gamma1*females_of_age[age]));
    double denominator = 1 + pow(M_E,gamma0 +(gamma1*females_of_age[age]));
    cout << "numerator:" << numerator << endl;
    cout << "denom:" << denominator << endl;
    if (denominator != 0) {
        //cout << "zlomek: " << numerator/denominator << endl;
        return numerator/denominator;
    }  
    else 
        return 0;
}*/

/*// Sk(t)
double Model::get_coef_surv() {
    // ai(t) - number of mothers of age i
    double sum = 0;
    for (int i = 0; i <= MAX_AGE; i++)
    {   
        cout << "newbown: " << get_newborn_females_cnt_per_age(i) << endl;
        sum += get_newborn_females_cnt_per_age(i)*(param.min_surv + max_min*get_gamma_function_result(i));
    }
    cout << "sum s0: " << sum << endl;
    return sum;
}*/

// nk(t+1) - number of females k months old
double Model::new_num_females_of_age() {
    
   for (int i = MAX_AGE-1; i >= 0; i--)
    {
        females_of_age[i+1] = coef_surv[i]*females_of_age[i];
    }
}

///////////////////////////////////////////////////////////////////////////

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
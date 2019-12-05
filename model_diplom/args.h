#ifndef IMS_ARGS
#define IMS_ARGS
    using namespace std;
    #include <stdio.h>
    #include <stdlib.h>
    #include <iostream>
    #include <unistd.h> //uint32_t

    typedef struct
    {
        double max_daughters_month = 0.0; // B  = B - max pocet dcer jedne samice za mesic
        uint32_t dens_b_half = 0;         // θ  = t - Hustota pri ktere je B = 1/2
        uint32_t norm_age_repro = 0;      // λ1 = l - obvykly vek pri prvni reprodukci
        uint32_t max_age_repro = 0;       // λ2 = L - max vek pri prvni reprodukci 
        uint32_t dens_repro_delayed = 0;  // c  = c - krit. hustota pro odlozeni reprodukce do dalsiho roku
        double min_surv = 0.0;            // σ1 = s - min. preziti (mesice)
        double max_surv = 0.0;            // σ2 = S - max. prezity (mesice)
        uint32_t mother_age_repro = 0;    // A  = A - matcin vek pri prvni reprodukci
        uint32_t max_age = 0;             // k  = k - max. vek (mesice)
    } Arguments;

    int parse_args(Arguments *args, int argc ,char *argv[]);
    int used_twice(int param);
    void print_usage();
    void print_args(Arguments args);


#endif
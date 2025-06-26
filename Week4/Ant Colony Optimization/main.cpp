#include "Alg.h"

int main(int argc, char *argv[]){
    int Run = atoi(argv[1]);
    int Iter = atoi(argv[2]);
    int Ant = atoi(argv[3]);
    double alpha = atof(argv[4]);
    double beta = atof(argv[5]);
    double rho = atof(argv[6]);
    double Q = atof(argv[7]);

    Alg algorithm;
    algorithm.RunALG(Run, Iter, Ant, alpha, beta, rho, Q);
}
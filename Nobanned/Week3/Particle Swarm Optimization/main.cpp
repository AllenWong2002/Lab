#include "Alg.h"

int main(int argc, char *argv[]){
    int Population = atoi(argv[1]);         // Population size
    int Dimension = atoi(argv[2]);          // Dimension size
    int Run = atoi(argv[3]);                // Number of runs

    Alg algorithm;
    algorithm.RunALG(Population, Dimension, Run);
}
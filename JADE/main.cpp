#include "Alg.h"

int main(int argc, char *argv[]){
    int Generation = atoi(argv[1]);         // Generation size
    int Population = atoi(argv[2]);         // Population size
    int Dimension = atoi(argv[3]);          // Dimension size
    int Run = atoi(argv[4]);                // Number of runs
    int FunctionID = atoi(argv[5]);        // Function ID

    Alg algorithm;
    algorithm.RunALG(Generation, Population, Dimension, Run, FunctionID);
}
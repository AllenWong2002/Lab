#ifndef ALG_H
#define ALG_H

#include "Ackley.cpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <random>
#include <fstream>
#include <filesystem>
#include <set>
#include <cfloat>
#include <algorithm>

using namespace std;

typedef struct Particle{
    // vector<double> velocity;
    vector<double> position;
    double fitness;
    Particle() : fitness(DBL_MAX){}
    // vector<double> personal_best_position;
    // double personal_best_val;
    // Particle() : personal_best_val(DBL_MAX) {}
}Particle;

namespace fs = std::filesystem;

class Alg : Ackley{
public:
    void RunALG(int, int, int);

private:
    // Input from Command-line Argument
    int Population;
    int Dimension;
    int Run;

    // calculate the evaluation
    int nfes;
    int mnfes;

    // Algorithm parameters
    double p = 0.05; // Selection rate
    double c = 0.1;  // Mutation rate
    double uF = 0.5;
    double uCR = 0.5;
    double lower_bound = -32.768;
    double upper_bound = 32.768;

    void Reset();
    void Init(vector<Particle> &, int, int, double, double);
    void Evaluation(const vector<double>&, double &);

    vector<Particle> particles;
};

#endif
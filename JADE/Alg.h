#ifndef ALG_H
#define ALG_H

#include "TestFunction.cpp"
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
    vector<double> position;
    double fitness;
    Particle() : fitness(DBL_MAX){}
} Particle;

namespace fs = std::filesystem;

class Alg : TestFunction{

public:
    void RunALG(int, int, int, int, int);

private:
    // Input from Command-line Argument
    int Generation;
    int Population;
    int Dimension;
    int Run;
    int FunctionID;

    // Algorithm parameters
    double p = 0.05; // Selection rate
    double c = 0.1;  // Mutation rate
    double uF = 0.5;
    double uCR = 0.5;
    double lower_bound;
    double upper_bound;

    void Reset();
    void Init(vector<Particle> &, int, int, int);
    void Evaluation(const vector<double>&, double &, int);

    vector<Particle> particles;
};

#endif
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

using namespace std;

typedef struct Particle{
    vector<double> velocity;
    vector<double> position;
    vector<double> personal_best_position;
    double personal_best_val;
    Particle() : personal_best_val(DBL_MAX) {}
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

    void Evaluation(const vector<double>&, double &);

    void Reset();
    void Init(vector<Particle> &, int, int, double, double);

    vector<Particle> swarm;
};

#endif
#ifndef ALG_H
#define ALG_H

#include "OneMax.cpp"
#include "Deception.cpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <random>
#include <fstream>
#include <filesystem>

using namespace std;

namespace fs = std::filesystem;

class Alg : OneMax, Deception 
{
public:
    void RunALG(int, int, int, double, string);

private:
    // Input from Command-line Argument
    int Bit;
    int Run;
    int Iter;
    double rate;
    string problem;

    // calculate the evaluation
    int nfes;
    int mnfes;

    void Evaluation(vector<int>, int &, string);

    void Reset();
    void Init();

    vector<int> sol;
};

#endif
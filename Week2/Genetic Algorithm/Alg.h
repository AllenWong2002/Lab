#ifndef ALG_H
#define ALG_H

#include "OneMax.cpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <random>
#include <fstream>
#include <filesystem>
#include <set>

using namespace std;

namespace fs = std::filesystem;

class Alg : OneMax
{
public:
    void RunALG(int, int, int, int);

private:
    // Input from Command-line Argument
    int Bit;
    int Run;
    int Iter;
    double rate;
    int population;

    // calculate the evaluation
    int nfes;
    int mnfes;

    void Evaluation(vector<vector<int>>, vector<int> &, int &);

    void Reset();
    void Init(set<vector<int>> &, vector<vector<int>> &, int);
};

#endif
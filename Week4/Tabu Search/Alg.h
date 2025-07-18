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
#include <algorithm>
#include <deque>

using namespace std;

namespace fs = std::filesystem;

class Alg : OneMax, Deception 
{
public:
    void RunALG(int, int, int, string);

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

    int Evaluation(string, string);

    void Reset();
    void Init();

    string sol;
    deque<string> tabu_list;
};

#endif
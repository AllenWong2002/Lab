#ifndef ALG_H
#define ALG_H

#include "OneMax.cpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <filesystem>
#include <string>

using namespace std;

namespace fs = std::filesystem;

class Alg : OneMax
{
public:
    void RunALG(int, int, int, double);

private:
    // Input from Command-line Argument
    int Bit;
    int Run;
    int Iter;
    double rate;

    // calculate the evaluation
    int nfes;
    int mnfes;

    void Evaluation(vector<int>, int &);

    void Reset();
    void Init();

    vector<int> solution;
};

#endif
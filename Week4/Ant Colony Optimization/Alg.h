#ifndef ALG_H
#define ALG_H

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <cmath>
#include <random>
#include <algorithm>
#include <limits>

using namespace std;

struct City{
    int id;
    double x, y;
};

class Alg{

public:
    void RunALG(int Run, int Iter, int Ant, double alpha, double beta, double rho, double Q);

private:
    struct ant{
        vector<int> tour;
        double length;
    };

    vector<City> cities;
    vector<vector<double>> distance;
    vector<vector<double>> pheromone;
    int num_cities;

    // Input from Command-line Argument
    int Bit;
    int Run;
    int Iter;
    int Ant;
    double alpha;
    double beta;
    double rho;
    double Q;
    double default_pheromone = 0.5;

    // calculate the evaluation
    // int nfes;
    // int mnfes;

    // vector<int> best;
    // vector<int> current;
    // vector<int> global_best_tour;
    // double global_best_length = numeric_limits<double>::infinity();
    int pheromone_reset_period = 10;
    int generation_counter = 0;

    void LoadCities(const string& filename);
    void ComputeDistances();
    double ComputeTourLength(const vector<int>& tour);
    int SelectNextCity(const vector<bool>& visited, int current_city, double alpha, double beta);
    void UpdatePheromones(const vector<ant>& ants, const vector<int>& best_tour, double rho, double Q);

    double Distance(const City& a, const City& b);
    double TourLength(const vector<int>& tour, const vector<City>& cities);
    void TwoOpt(std::vector<int>& tour, const std::vector<City>& cities);
    void Mutate(std::vector<int>& tour, double pmut);
    bool IsEdgeInTour(int from, int to, const vector<int>& tour);
};

#endif

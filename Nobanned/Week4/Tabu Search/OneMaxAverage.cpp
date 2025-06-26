#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

int main(){
    const int num_runs = 30;
    const string folder = "output/";
    const int max_iterations = 60; // 根據你的 Iter 設定

    vector<double> sum_fitness(max_iterations + 1, 0.0);
    vector<int> count(max_iterations + 1, 0);

    for (int run = 1; run <= num_runs; ++run){
        string filename = folder + "OneMax_" + to_string(run) + ".txt";
        ifstream infile(filename);

        if (!infile){
            cerr << "Cannot open file: " << filename << endl;
            continue;
        }

        int iteration;
        double fitness;

        while (infile >> iteration >> fitness){
            if (iteration <= max_iterations){
                sum_fitness[iteration] += fitness;
            }
        }

        infile.close();
    }

    ofstream outfile("OneMaxResult.txt");
    if (!outfile){
        cerr << "Cannot create result.txt" << endl;
        return 1;
    }

    for (int i = 0; i <= max_iterations; ++i){
        double avg = sum_fitness[i] / num_runs;
        outfile << i << " " << fixed << setprecision(6) << avg << endl;
    }

    outfile.close();
    cout << "Averaged results written to result.txt" << endl;

    return 0;
}

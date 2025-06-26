#include "Alg.h"

void Alg::RunALG(int _Bit, int _Run, int _Iter, int _population){
    Bit = _Bit;
    Run = _Run;
    Iter = _Iter, mnfes = _Iter;
    population = _population;

    cout << Bit << " " << Run << " " << Iter << " " << population << endl;

    double crossover_rate = 0.6, mutation_rate = 0.1;
    vector<vector<int>> sol, New;
    set<vector<int>> unique_solutions;
    vector<int> answer(Bit, 0), parent1(Bit, 0), parent2(Bit, 0);

    random_device r;
    mt19937 gen(r());  
    uniform_real_distribution<double> dis(nextafter(0.0, 1.0), nextafter(1.0, 0.0));

    if (!fs::exists("output")){
        fs::create_directory("output");
    }

    srand(time(NULL));
    for (int i = 0; i < Run; i++){
        Reset();

        int current = 0, best = 0;

        sol.clear();
        sol.resize(population, vector<int>(Bit, 0));
        Init(unique_solutions, sol, population);
        Evaluation(sol, parent1, current);

        ofstream outfile;
        string filename = "output/Run_" + to_string(i + 1) + ".txt";
        outfile.open(filename);

        outfile << nfes - population << " " << current << endl;

        while (nfes < mnfes){
            New.clear();
            New.resize(population, vector<int>(Bit, 0));
            Init(unique_solutions, New, population);
            Evaluation(New, parent2, current);
            
            // 單點交配
            int index = rand() % Bit;
            double random = dis(gen);
            if(random < crossover_rate){
                for(int j = index; j < Bit; j++){
                    swap(parent1[j], parent2[j]);
                }
            }

            // 突變
            for(int j = 0; j < Bit; j++){
                double random = dis(gen);
                if(random < mutation_rate){
                    parent1[j] = 1 - parent1[j];
                }
            }
            for(int j = 0; j < Bit; j++){
                double random = dis(gen);
                if(random < mutation_rate){
                    parent2[j] = 1 - parent2[j];
                }
            }
            
            if(OneMaxProblem(parent1, Bit) > OneMaxProblem(parent2, Bit)){
                current = OneMaxProblem(parent1, Bit);
                if(current > best){
                best = current;
                answer = parent1;
                }
            }else{
                current = OneMaxProblem(parent2, Bit);
                if(current > best){
                    best = current;
                    answer = parent2;
                }
            }
            parent1 = answer;

            nfes += 2;
            cout << "Evaluation: " << nfes << ", Best Value: " << best << ", Answer: ";
            for (size_t k = 0; k < answer.size(); ++k) {
                cout << answer[k];
                if (k != answer.size() - 1)
                    cout << " ";
            }
            cout << endl;
            outfile << nfes - population << " " << best << endl;
        }
    }
}

void Alg::Evaluation(vector<vector<int>> sol, vector<int> &parent, int &value){
    int max = 0;
    for(int i = 0; i < population; i++){
        value = OneMaxProblem(sol[i], Bit);
        nfes++;
        if(value > max){
            max = i;
        }
    }
    parent = sol[max];
    value = OneMaxProblem(parent, Bit);
}

void Alg::Reset(){
    nfes = 0;
}

void Alg::Init(set<vector<int>> &unique_solutions, vector<vector<int>> &sol, int population){
    unique_solutions.clear();
    while (sol.size() < population){
        vector<int> unique(Bit);
        for(int i = 0; i < Bit; i++){
            unique[i] = rand() % 2;
        }
        if(unique_solutions.insert(unique).second){
            sol.push_back(unique);
        }
    }
}

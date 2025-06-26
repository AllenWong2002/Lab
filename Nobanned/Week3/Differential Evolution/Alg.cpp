#include "Alg.h"

void Alg::RunALG(int _Population, int _Dimension, int _Run){
    Population = _Population;
    Dimension = _Dimension;
    mnfes = Dimension * 10000;
    Run = _Run;

    cout << Population << " " << Dimension << endl;

    double F = 0.5;          // 擴張係數
    double CR = 0.9;         // 交叉率

    // if(!fs::exists("output")){
    //     fs::create_directory("output");
    // }

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> r(0.0, 1.0);

    for(int i = 0; i < Run; i++){
        // ofstream outfile;
        // string filename = "output/Run_" + to_string(i + 1) + ".txt";
        // outfile.open(filename);

        vector<double> global_best_position(Dimension, 32.768);
        double global_best_val = DBL_MAX;

        Reset();

        Init(individule, Population, Dimension, -32.768, 32.768);

        while(nfes < mnfes){
            for(int i = 0; i < Population; i++){
                // Mutation
                vector<int> idx;
                for (int j = 0; j < Population; j++) {
                    if (j != i) idx.push_back(j);
                }
                shuffle(idx.begin(), idx.end(), gen);
                int a = idx[0], b = idx[1], c = idx[2];

                vector<double> mutant(Dimension);
                for(int d = 0; d < Dimension; d++){
                    mutant[d] = individule[a].position[d] + F * (individule[b].position[d] - individule[c].position[d]);
                    if (mutant[d] < -32.768)
                        mutant[d] = -32.768;
                    if (mutant[d] > 32.768)
                        mutant[d] = 32.768;
                }

                // Crossover
                vector<double> trial(Dimension);
                int R = gen() % Dimension;
                for (int d = 0; d < Dimension; d++) {
                    if (r(gen) < CR || d == R)
                        trial[d] = mutant[d];
                    else
                        trial[d] = individule[i].position[d];
                }

                // Selection
                double trial_fitness;
                Evaluation(trial, trial_fitness);
                if(trial_fitness < individule[i].fitness){
                    individule[i].position = trial;
                    individule[i].fitness = trial_fitness;
                }
            }

            global_best_val = individule[0].fitness;
            for(int i = 1; i < Population; i++){
                if(individule[i].fitness < global_best_val)
                    global_best_position = individule[i].position;
                    global_best_val = individule[i].fitness;
            }

            // outfile << (nfes - Population) / Population << " " << global_best_val << endl;
            cout << "nfes: " << nfes << ", Best Value: " << global_best_val << ", Best Position: ";
            for (const auto& pos : global_best_position) {
                cout << pos << " ";
            }
            cout << endl;
        }
    }
}

void Alg::Evaluation(const vector<double>& position, double &value){
    value = AckleyFunction(position);
    nfes++;
}

void Alg::Reset(){
    nfes = 0;
}

void Alg::Init(vector<Particle> &individule, int population, int dimension, double xmin, double xmax){
    individule.clear();
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(xmin, nextafter(xmax, DBL_MAX));

    for (int i = 0; i < population; i++){
        Particle p;
        p.position.resize(dimension);
        for (int j = 0; j < dimension; j++){
            p.position[j] = dis(gen);
        }
        Evaluation(p.position, p.fitness);
        individule.push_back(p);
    }
}

#include "Alg.h"

void Alg::RunALG(int _Bit, int _Run, int _Iter, double _Rate, string _problem){
    Bit = _Bit;
    Run = _Run;
    Iter = _Iter, mnfes = _Iter;
    rate = _Rate;
    problem = _problem;

    cout << Bit << " " << Run << " " << Iter << " " << rate << " " << problem << endl;

    if (!fs::exists("output")){
        fs::create_directory("output");
    }

    for (int i = 0; i < Run; i++){
        Reset();

        Init();

        int current = 0;
        Evaluation(sol, current, problem);
        
        ofstream outfile;
        if(problem == "Deception"){
            string filename = "output/Deception_" + to_string(i + 1) + ".txt";
            outfile.open(filename);
        }else if(problem == "OneMax"){
            string filename = "output/OneMax_" + to_string(i + 1) + ".txt";
            outfile.open(filename);
        }

        outfile << nfes - 1 << " " << current << endl;

        double T = 100;

        while (nfes < mnfes){
            vector<int> New_sol = sol;              
            int idx = rand() % Bit;             
            New_sol[idx] = 1 - New_sol[idx];

            int New;
            Evaluation(New_sol, New, problem);

            if(New >= current){
                current = New;
                sol = New_sol;
            }else{
                double P = exp((New - current) / T);
                random_device r;
                mt19937 gen(r());
                uniform_real_distribution<double> dis(nextafter(0.0, 1.0), nextafter(1.0, 0.0));
                double random = dis(gen);
                if(random < P){
                    current = New;
                    sol = New_sol;
                }
                // cout << P << " " << random << endl;
            }
            T *= rate;    // 降溫
            cout << "Iteration: " << nfes << ", Best Value: " << current << ", Answer: ";
            for (size_t k = 0; k < sol.size(); ++k) {
                cout << sol[k];
                if (k != sol.size() - 1)
                    cout << " ";
            }
            cout << endl;
            outfile << nfes - 1 << " " << current << endl;
        }
    }
}

void Alg::Evaluation(vector<int> sol, int &value, string problem){
    if (problem == "Deception")
        value = DeceptionProblem(sol, Bit);
    else if (problem == "OneMax")
        value = OneMaxProblem(sol, Bit);
    nfes++;
}

void Alg::Reset(){
    nfes = 0;
}

void Alg::Init(){
    sol.clear();
    for (int i = 0; i < Bit; i++){
        sol.push_back(rand() % 2);      // 隨機 0 或 1
    }
}

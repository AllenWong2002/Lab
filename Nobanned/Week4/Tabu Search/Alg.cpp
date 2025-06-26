#include "Alg.h"

void Alg::RunALG(int _Bit, int _Run, int _Iter, string _problem){
    Bit = _Bit;
    Run = _Run;
    Iter = _Iter, mnfes = _Iter;
    problem = _problem;

    cout << Bit << " " << Run << " " << Iter << " " << problem << endl;

    if (!fs::exists("output")){
        fs::create_directory("output");
    }
    // srand(time(NULL));

    for (int i = 0; i < Run; i++){
        Reset();

        Init();

        int best_value = 0, length = 1000, n = 50, count = 1;
        best_value = Evaluation(sol, problem);
        string best = sol;
        tabu_list.push_front(sol);

        cout << "Run: " << i + 1 << ", NFES: " << (nfes - 1) / 99 << ", Best Value: " << best_value << ", Best Solution: ";
        for (char c : best) {
            cout << c;
        }
        cout << endl;

        ofstream outfile;
        if(problem == "Deception"){
            string filename = "output/Deception_" + to_string(i + 1) + ".txt";
            outfile.open(filename);
        }else if(problem == "OneMax"){
            string filename = "output/OneMax_" + to_string(i + 1) + ".txt";
            outfile.open(filename);
        }

        outfile << count++ << " " << best_value << endl;


        while (nfes < mnfes){
            if(int(tabu_list.size()) >= length){
                tabu_list.pop_front();
            }
            string R = sol;
            int index = rand() % Bit;
            R[index] = (R[index] == '0') ? '1' : '0';           // 隨機選擇一個位置，將其值反轉

            for (int j = 0; j < n - 1; j++){
                // int value_r = 0, value_w = 0;
                string W = sol;
                index = rand() % Bit;
                W[index] = (W[index] == '0') ? '1' : '0';

                if((find(tabu_list.begin(), tabu_list.end(), W) == tabu_list.end()) && ((Evaluation(W, problem) > Evaluation(R, problem)) || find(tabu_list.begin(), tabu_list.end(), R) != tabu_list.end())){
                    R = W;                      // 如果 W 不在 tabu_list 中，且 W 的評估值大於 R 或 R 在 tabu_list 中，則更新 R
                }
            }
            if(find(tabu_list.begin(), tabu_list.end(), R) == tabu_list.end()){
                sol = R;                        // 如果 R 不在 tabu_list 中，則更新當前解
                tabu_list.push_front(R);
            }

            int temp = Evaluation(sol, problem);
            if(temp > best_value){
                best_value = temp;              // 如果當前解的評估值大於之前的最佳解，則更新最佳解
                best = sol;
            }
            cout << "Run: " << i + 1 << ", NFES: " << (nfes - 1) / 99 << ", Best Value: " << best_value << ", Best Solution: ";
            for (char c : best) {
                cout << c;
            }
            cout << endl;
            outfile << count++ << " " << best_value << endl;
        }
    }
}

int Alg::Evaluation(string sol, string problem){
    nfes++;
    if(problem == "Deception")
        return DeceptionProblem(sol, Bit);
    else if(problem == "OneMax")
        return OneMaxProblem(sol, Bit);
    return -1;                                          // 如果問題類型不正確，返回 -1
}

void Alg::Reset(){
    nfes = 0;
}

void Alg::Init(){
    tabu_list.clear();
    sol.clear();
    for (int i = 0; i < Bit; i++){
        sol.push_back((rand() % 2) ? '1' : '0');        // 隨機 0 或 1
    }
}

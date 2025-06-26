#include "Alg.h"

void Alg::RunALG(int _Bit, int _Run, int _Iter, double _Rate)
{
    Bit = _Bit;
    Run = _Run;
    Iter = _Iter;
    rate = _Rate;

    cout << Bit << " " << Run << " " << Iter << " " << rate << endl;

    srand(time(0)); // 初始化亂數種子

    if (!fs::exists("output")) {
        fs::create_directory("output");
    }

    for (int i = 0; i < Run; i++)
    {
        Reset();

        Init();

        //世代數(iteration)跟計算次數(evaluation)二擇一使用
        //跟其他演算法比較通常都是使用evaluation，故建議使用evaluation

        int best_value;
        Evaluation(solution, best_value); // 計算初始解適應值

        string filename = "output/Run_" + to_string(i + 1) + ".txt";
        ofstream outfile(filename);

        outfile << "0" << " " << best_value << endl;

        for (int j = 0; j < Iter; j++) /*Iteration (世代數) */
        {
            vector<int> neighbor = solution;

            int random_flip = rand() % Bit;
            neighbor[random_flip] = 1 - neighbor[random_flip];

            int neighbor_value;
            Evaluation(neighbor, neighbor_value);

            if (neighbor_value > best_value){
                solution = neighbor;
                best_value = neighbor_value;
            }else if (neighbor_value == best_value){
                solution = neighbor;
            }

            outfile << j + 1 << " " << best_value << endl;
            
            cout << "Run: " << i + 1 << ", Evaluations = " << best_value << endl;
            cout << "Solution: ";
            for(int s:solution){
                cout << s;
            }
            cout << endl;
        }
    }
}

void Alg::Evaluation(vector<int> sol, int &value)
{
    value = OneMaxProblem(sol, Bit);
    nfes++;
}

void Alg::Reset()
{
    nfes = 0;
}

void Alg::Init()
{
    solution.clear();
    for (int i = 0; i < Bit; i++){
        solution.push_back(rand() % 2); // 隨機 0 或 1
    }
}

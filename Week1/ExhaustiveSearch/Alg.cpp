#include "Alg.h"

void Alg::RunALG(int _Bit, int _Run, int _Iter, double _Rate)
{
    Bit = _Bit;
    Run = _Run;
    Iter = _Iter;
    rate = _Rate;

    cout << Bit << " " << Run << " " << Iter << " " << rate << endl;
    
    for (int i = 0; i < Run; i++)
    {
        Reset();

        Init();

        const int time_limit = 1800; // 30 分鐘 = 1800 秒
        time_t start_time = time(nullptr);

        while(1 && Increment(current)){
            time_t now = time(nullptr);
            if (difftime(now, start_time) >= time_limit){
                cout << "Reached 30 minutes, terminated!!!" << endl;
                break;
            }
            
            // std::this_thread::sleep_for(std::chrono::seconds(1));
            
            if (OneMaxProblem(current, Bit) > OneMaxProblem(best, Bit))
                best = current;
            
            nfes++;
            if (nfes % 1000 == 0){
                int elapsed = static_cast<int>(difftime(now, start_time));
                cout << "nfes: " << nfes << " | elapsed: " << elapsed << "s" << endl;
                for (int b : best)
                    cout << b;
                cout << endl;
            }
        }
        for (int b : best)
            cout << b;
        cout << endl;
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
    /*Initialize*/
    current = vector<int>(Bit, 0);
    best = current;
}

bool Alg::Increment(vector<int>& current)
{
    for (int i = Bit - 1; i >= 0; --i)
    {
        if (current[i] == 0)
        {
            current[i] = 1;
            for (int j = i + 1; j < Bit; ++j)
                current[j] = 0;
            return true; // 還可以繼續加
        }
    }
    return false; // 已經到最後一組（111...1）
}

#include <vector>
#include <cmath>

class Deception{

public:
    int DeceptionProblem(std::vector<int> sol, int bit_size){
        int decimal = 0, Pow2Nminus2 = pow(2, bit_size - 2);
        for (int i = 0; i < bit_size; i++){         // 轉成10進位數
            decimal += sol[i] * pow(2,i);
        }
        return abs(decimal - Pow2Nminus2);
    }
};
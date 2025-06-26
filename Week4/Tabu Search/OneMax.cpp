#include <vector>
#include <string>

class OneMax{

public:
    int OneMaxProblem(std::string sol, int bit_size){
        int sum = 0;
        for (int i = 0; i < bit_size; i++){
            sum += (sol[i] - '0');
        }
        return sum;
    }
};
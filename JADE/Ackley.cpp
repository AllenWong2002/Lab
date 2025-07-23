#include <vector>
#include <math.h>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

class Ackley{

public:
    double AckleyFunction(const vector<double> &position){
        int n = position.size();
        double sum1 = 0.0, sum2 = 0.0;

        for (int i = 0; i < n; i++){
            sum1 += position[i] * position[i];
            sum2 += cos(2 * M_PI * position[i]);
        }
        
        double answer = -20 * exp(-0.2 * sqrt(sum1 / n)) - exp(sum2 / n) + 20 + exp(1.0);
        return answer;
    }
};
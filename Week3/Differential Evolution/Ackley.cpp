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
        const double a = 20.0;
        const double b = 0.2;
        const double c = 2 * M_PI;

        int n = position.size();
        double sum1 = 0.0, sum2 = 0.0;

        for (int i = 0; i < n; i++) {
            sum1 += position[i] * position[i];
            sum2 += cos(c * position[i]);
        }
        double answer = -a * exp(-b * sqrt(sum1 / n)) - exp(sum2 / n) + a + exp(1.0);
        
        return answer;
    }
};
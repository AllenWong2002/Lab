#include <vector>
#include <cmath>
#include <random>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

class TestFunction{

public:
    double SphereFunction(const vector<double> &position){
        double answer = 0.0;
        for(double x : position){
            answer += x * x;
        }
        return answer;
    }

    double SchwefelFunction2_22(const vector<double> &position){
        double sum = 0.0, product = 1.0;
        for(double x : position){
            sum += fabs(x);
            product *= fabs(x);
        }
        double answer = sum + product;
        return answer;
    }

    double SchwefelFunction1_2(const vector<double> &position){
        double sum = 0.0;
        double answer = 0.0;
        for(double x : position){
            sum += x;
            answer += pow(sum, 2);
        }
        return answer;
    }

    double SchwefelFunction2_21(const vector<double> &position){
        double answer = fabs(position[0]);
        for(double x : position){
            if(fabs(x) > answer)
                answer = fabs(x);
        }
        return answer;
    }

    double RosenbrockFunction(const vector<double> &position){
        double answer = 0.0;
        for(size_t i = 0; i < position.size() - 1; i++){
            double x = position[i];
            double y = position[i + 1];
            answer += (100 * pow(y - (x * x), 2) + pow(x - 1, 2));
        }
        return answer;
    }

    double StepFunction(const vector<double> &position){
        double answer = 0.0;
        for(double x : position) 
            answer += pow(floor(x + 0.5), 2);
        return answer;
    }

    double NoisyQuadraticFunction(const vector<double> &position){
        double answer = 0.0;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        double noise = dis(gen);

        for(size_t i = 0; i < position.size(); i++){
            answer += (i + 1) * pow(position[i], 4);
        }
        answer += noise;
        return answer;
    }

    double SchwefelFunction2_26(const vector<double> &position){
        double answer = 0.0;
        for(double x : position){
            answer += (-x * sin(sqrt(fabs(x))));
        }
        answer += (418.98288727243369 * position.size());
        return answer;
    }

    double RastriginFunction(const vector<double> &position){
        double answer = 0.0;
        for(double x : position){
            answer += (pow(x, 2) - (10 * cos(2 * M_PI * x)) + 10);
        }
        return answer;
    }

    double AckleyFunction(const vector<double> &position){
        int n = position.size();
        double sum1 = 0.0, sum2 = 0.0;

        for(double x : position){
            sum1 += pow(x, 2);
            sum2 += cos(2 * M_PI * x);
        }
        
        double answer = -20 * exp(-0.2 * sqrt(sum1 / n)) - exp(sum2 / n) + 20 + exp(1.0);
        return answer;
    }

    double GriewankFunction(const vector<double> &position){
        double sum = 0.0, product = 1.0;
        for(size_t i = 0; i < position.size(); i++){
            sum += pow(position[i], 2);
            product *= cos(position[i] / sqrt(i + 1));
        }
        sum /= 4000.0;
        double answer = sum - product + 1;
        return answer;
    }

    double PenalizedFunction1(const vector<double> &position){
        int D = position.size();
        int a = 10, k = 100, m = 4;
        vector<double> y(D);
        for(int i = 0; i < D; i++)
            y[i] = 1 + ((position[i] + 1) / 4);

        double answer = 10 * pow(sin(M_PI * y[0]), 2);
        for(int i = 0; i < D - 1; i++){
            answer += (pow(y[i] - 1, 2) * (1 + 10 * pow(sin(M_PI * y[i + 1]), 2)));
        }
        answer += pow(y[D - 1] - 1, 2);
        answer = ((answer * M_PI) / D);

        for(double x : position){
            if(x > a)
                answer += (k * pow((x - a), m));
            else if(x >= -a && x <= a)
                answer += 0;
            else
                answer += (k * pow((-x - a), m));
        }
        return answer;
    }

    double PenalizedFunction2(const vector<double> &position){
        int D = position.size();
        int a = 5, k = 100, m = 4;
        double answer = pow(sin(3 * M_PI * position[0]), 2);
        for (int i = 0; i < D - 1; ++i){
            answer += pow((position[i] - 1), 2) * (1 + pow(sin(3 * M_PI * position[i + 1]), 2));
        }
        answer += (pow((position[D - 1] - 1), 2) * (1 + pow(sin(2 * M_PI * position[D - 1]), 2)));
        answer *= 0.1;
        for (double x : position) {
            if(x > a)
                answer += (k * pow((x - a), m));
            else if(x >= -a && x <= a)
                answer += 0;
            else
                answer += (k * pow((-x - a), m));
        }
        return answer;
    }
};
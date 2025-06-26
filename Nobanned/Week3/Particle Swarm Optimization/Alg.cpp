#include "Alg.h"

void Alg::RunALG(int _Population, int _Dimension, int _Run){
    Population = _Population;
    Dimension = _Dimension;
    mnfes = Dimension * 10000;
    Run = _Run;

    cout << Population << " " << Dimension << endl;

    if (!fs::exists("output")){
        fs::create_directory("output");
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> r(0.0, nextafter(1.0, DBL_MAX));
    for (int i = 0; i < Run; i++){
        ofstream outfile;
        string filename = "output/Run_" + to_string(i + 1) + ".txt";
        outfile.open(filename);

        Reset();

        Init(swarm, Population, Dimension, -32.768, 32.768);
        vector<double> global_best_position(Dimension, 32.768);
        double global_best_val = DBL_MAX;

        while(nfes < mnfes){
            for (int i = 0; i < Population; i++){
                for (int d = 0; d < Dimension; d++){
                    double φ1 = r(gen), φ2 = r(gen);
                    double ω_max = 0.9, ω_min = 0.4;                            // 慣性權重
                    double ω = ω_max - ((ω_max - ω_min) * nfes) / mnfes;        // 動態慣性權重
                    double toward_pBest = 1.5, toward_gBest = 1.5;              // 個體加速因子和社會加速因子

                    swarm[i].velocity[d]                                        // 粒子速度更新公式
                    = ω * swarm[i].velocity[d]
                    + toward_pBest * φ1 * (swarm[i].personal_best_position[d] - swarm[i].position[d])
                    + toward_gBest * φ2 * (global_best_position[d] - swarm[i].position[d]);

                    swarm[i].position[d] += swarm[i].velocity[d];               // 粒子位置更新公式
                    
                    if(swarm[i].position[d] < -32.768){                         // 確保粒子位置在邊界內
                        swarm[i].position[d] = -32.768;
                    }else if(swarm[i].position[d] > 32.768){
                        swarm[i].position[d] = 32.768;
                    }
                }

                double value;
                Evaluation(swarm[i].position, value);

                if(value < swarm[i].personal_best_val){                         // 更新個體最優解
                    swarm[i].personal_best_val = value;
                    swarm[i].personal_best_position = swarm[i].position;
                }
                if(value < global_best_val){                                    // 更新全局最優解
                    global_best_val = value;
                    global_best_position = swarm[i].position;
                }
            }
            outfile << (nfes - Population) / Population << " " << global_best_val << endl;
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

void Alg::Init(vector<Particle> &swarm, int population, int dimension, double xmin, double xmax){
    swarm.clear();
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(xmin, nextafter(xmax, DBL_MAX));
    uniform_real_distribution<> vdis(-(xmax - xmin) * 0.1, (xmax - xmin) * 0.1);

    for (int i = 0; i < population; i++){
        Particle p;
        p.position.resize(dimension);
        p.velocity.resize(dimension);
        p.personal_best_position.resize(dimension);
        for (int j = 0; j < dimension; j++){
            p.position[j] = dis(gen);
            p.velocity[j] = vdis(gen);
            p.personal_best_position[j] = p.position[j];
        }
        Evaluation(p.position, p.personal_best_val);
        swarm.push_back(p);
    }
}

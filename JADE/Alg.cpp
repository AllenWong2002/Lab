#include "Alg.h"

void Alg::RunALG(int _Generation, int _Population, int _Dimension, int _Run, int _FunctionID){
    Generation = _Generation;
    Population = _Population;
    Dimension = _Dimension;
    Run = _Run;
    FunctionID = _FunctionID;

    const int pbest_percent = max(2, int(p * Population));      // 至少選2人當p-best候選

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> rand01(0.0, nextafter(1.0, DBL_MAX));
    cauchy_distribution<> randF(uF, 0.1);
    normal_distribution<> randCR(uCR, 0.1);

    vector<double> each_run_best;

    for(int run = 0; run < Run; run++){
        Reset();
        Init(particles, Population, Dimension, FunctionID);
        vector<Particle> archive;
        Particle best;

        for(int g = 0; g < Generation; g++){
            vector<double> SF, SCR;     // 成功的 F, CR之集合

            // sort population by fitness (for p-best selection)
            sort(particles.begin(), particles.end(), [](const Particle &a, const Particle &b){
                return a.fitness < b.fitness;
            });

            for(int i = 0; i < Population; i++){
                // ========== Adaptive CR and F ==========
                double CR, F;
                do{
                    CR = randCR(gen);
                }while (CR < 0.0 || CR > 1.0);

                do{
                    F = randF(gen);
                }while (F <= 0.0);

                F = min(F, 1.0);        // F > 1, 則設為1

                // ========== Select p-best individual ==========
                int pbest_index = rand() % pbest_percent;
                const vector<double> &pbest = particles[pbest_index].position;

                // ========== Select random r1, r2 (r2 may come from archive) ==========
                int r1_index, r2_index;
                set<int> exclude = {i, pbest_index};        // 裝不能被選到的索引之集合
                vector<int> candidates;
                for(int j = 0; j < Population; j++)
                    if(!exclude.count(j))
                        candidates.push_back(j);
                shuffle(candidates.begin(), candidates.end(), gen);
                Particle r1 = particles[candidates[0]];
                r1_index = candidates[0];
                exclude.insert(r1_index);

                vector<Particle> union_pool = particles;
                union_pool.insert(union_pool.end(), archive.begin(), archive.end());
                shuffle(union_pool.begin(), union_pool.end(), gen);

                Particle r2;
                vector<Particle> valid_candidates;
                for(const auto &candidate : union_pool){
                    if(candidate.position != particles[i].position &&
                        candidate.position != particles[r1_index].position &&
                        candidate.position != particles[pbest_index].position){
                        valid_candidates.push_back(candidate);
                    }
                }

                if(!valid_candidates.empty()){
                    shuffle(valid_candidates.begin(), valid_candidates.end(), gen);
                    r2 = valid_candidates[0];
                }else{
                    // fallback：若candidates為空, 就從 population 裡挑一個不重複的
                    std::uniform_int_distribution<> dist_pop(0, Population - 1);
                    do{
                        r2_index = dist_pop(gen);
                    }while(exclude.count(r2_index));
                    r2 = particles[r2_index];
                }

                // ========== current-to-pbest mutation ==========
                vector<double> mutant(Dimension);           // mutant -> v
                for(int d = 0; d < Dimension; d++){
                    mutant[d] = particles[i].position[d]
                                + F * (pbest[d] - particles[i].position[d])
                                + F * (r1.position[d] - r2.position[d]);
                    while(mutant[d] < lower_bound)
                        mutant[d] = (lower_bound + particles[i].position[d]) / 2.0;
                    while(mutant[d] > upper_bound)
                        mutant[d] = (upper_bound + particles[i].position[d]) / 2.0;
                }

                // ========== Crossover ==========
                vector<double> trial(Dimension);            // trial -> u
                int J = gen() % Dimension;
                for(int j = 0; j < Dimension; j++){
                    if(j == J || rand01(gen) < CR)
                        trial[j] = mutant[j];
                    else
                        trial[j] = particles[i].position[j];
                }

                // ========== Selection ==========
                double trial_fitness;
                Evaluation(trial, trial_fitness, FunctionID);
                if(particles[i].fitness < trial_fitness)
                    continue;
                else{
                    particles[i].position = trial;
                    particles[i].fitness = trial_fitness;
                    archive.push_back(particles[i]);        // 將被淘汰的個體加入archive
                    SF.push_back(F);
                    SCR.push_back(CR);
                }
            }

            // ========== Archive control ==========
            while(int(archive.size()) > Population)
                archive.erase(archive.begin() + rand() % archive.size());

            // ========== Update uF, uCR ==========
            if(!SCR.empty()){
                // 更新 uCR : Arithmetic mean
                double meanA_SCR = 0.0;
                for (double cr : SCR) 
                    meanA_SCR += cr;
                meanA_SCR /= SCR.size();
                uCR = (1.0 - c) * uCR + c * meanA_SCR;
            }
            if(!SF.empty()){
                // 更新 uF：Lehmer mean
                double F_square = 0.0, F_sum = 0.0;
                for(double f : SF){
                    F_square += f * f;
                    F_sum += f;
                }
                if(F_sum != 0.0)
                    uF = F_square / F_sum;
            }

            // ========== Output ==========
            best = *min_element(particles.begin(), particles.end(), [](const Particle &a, const Particle &b){
                return a.fitness < b.fitness;
            });

            cout << "Generation: " << g << ", Best Value: " << best.fitness << endl;
            // << ", Best Position: ";
            // for(const auto &val : best.position) 
            //     cout << val << " ";
            // cout << endl;
            cout << "Generation: " << Generation << ", Population: " << Population << ", Dimension: " << Dimension << ", Run: " << Run << ", FunctionID: " << FunctionID << endl;
        }
        each_run_best.push_back(best.fitness);
    }
    cout << "Average Best Value over " << Run << " runs: ";
    double average_best = accumulate(each_run_best.begin(), each_run_best.end(), 0.0) / each_run_best.size();
    cout << average_best << endl;
}

void Alg::Reset(){
    p = 0.05;
    c = 0.1;
    uF = 0.5;
    uCR = 0.5;
}

void Alg::Init(vector<Particle> &particles, int population, int dimension, int function_id){
    switch(function_id){
        case 1: lower_bound = -100.0; upper_bound = 100.0; break;
        case 2: lower_bound = -10.0; upper_bound = 10.0; break;
        case 3: lower_bound = -100.0; upper_bound = 100.0; break;
        case 4: lower_bound = -100.0; upper_bound = 100.0; break;
        case 5: lower_bound = -30.0; upper_bound = 30.0; break;
        case 6: lower_bound = -100.0; upper_bound = 100.0; break;
        case 7: lower_bound = -1.28; upper_bound = 1.28; break;
        case 8: lower_bound = -500.0; upper_bound = 500.0; break;
        case 9: lower_bound = -5.12; upper_bound = 5.12; break;
        case 10: lower_bound = -32.768; upper_bound = 32.768; break;
        case 11: lower_bound = -600.0; upper_bound = 600.0; break;
        case 12: lower_bound = -50.0; upper_bound = 50.0; break;
        case 13: lower_bound = -50.0; upper_bound = 50.0; break;
        default: throw invalid_argument("Invalid function ID");
    }

    particles.clear();
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(lower_bound, nextafter(upper_bound, DBL_MAX));

    for (int i = 0; i < population; i++){
        Particle p;
        p.position.resize(dimension);
        for (int j = 0; j < dimension; j++){
            p.position[j] = dis(gen);
        }
        Evaluation(p.position, p.fitness, FunctionID);
        particles.push_back(p);
    }
}

void Alg::Evaluation(const vector<double>& position, double &value, int function_id){
    switch(function_id){
        case 1: value = SphereFunction(position); break;
        case 2: value = SchwefelFunction2_22(position); break;
        case 3: value = SchwefelFunction1_2(position); break;
        case 4: value = SchwefelFunction2_21(position); break;
        case 5: value = RosenbrockFunction(position); break;
        case 6: value = StepFunction(position); break;
        case 7: value = NoisyQuadraticFunction(position); break;
        case 8: value = SchwefelFunction2_26(position); break;
        case 9: value = RastriginFunction(position); break;
        case 10: value = AckleyFunction(position); break;
        case 11: value = GriewankFunction(position); break;
        case 12: value = PenalizedFunction1(position); break;
        case 13: value = PenalizedFunction2(position); break;
        default: throw invalid_argument("Invalid function ID");
    }
}
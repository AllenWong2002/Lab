#include "Alg.h"

void Alg::RunALG(int _Run, int _Iter, int _Ant, double _Alpha, double _Beta, double _Rho, double _Q){
    Run = _Run;
    Iter = _Iter;
    Ant = _Ant;
    alpha = _Alpha;
    beta = _Beta;
    rho = _Rho;
    Q = _Q;

    // alpha控制費洛蒙影響力 beta控制啟發式資訊影響力 rho蒸發率 Q費洛蒙增強常數
    cout << Run << " runs, " << Iter << " iterations, " << Ant << " ants, " << "alpha: " << alpha << ", beta: " << beta << ", rho: " << rho << ", Q: " << Q << "\n";

    for (int i = 0; i < Run; i++){
        LoadCities("ACO_HW_point.txt");

        ComputeDistances();

        // double alpha = 2.1, beta = 4.5, rho = 0.1, Q = 500.0;                   // alpha控制費洛蒙影響力 beta控制啟發式資訊影響力 rho蒸發率 Q費洛蒙增強常數
        vector<int> best_tour;
        double best_length = numeric_limits<double>::infinity();

        for (int j = 0; j < Iter; ++j){
            vector<ant> ants(Ant);
            for (auto& ant : ants){
                ant.tour.clear();                                               // 初始化每隻螞蟻的路徑
                vector<bool> visited(num_cities, false);
                uniform_int_distribution<> dist(0, num_cities - 1);
                default_random_engine gen(random_device{}());
                int current = dist(gen);
                ant.tour.push_back(current);
                visited[current] = true;

                for (int step = 1; step < num_cities; ++step){                  // 輪盤法選擇下一個城市
                    int next = SelectNextCity(visited, current, alpha, beta);
                    ant.tour.push_back(next);
                    visited[next] = true;
                    current = next;
                }
                ant.length = ComputeTourLength(ant.tour);
                // Mutate(ant.tour, 0.05);
                TwoOpt(ant.tour, cities);
                ant.length = ComputeTourLength(ant.tour);

                if (ant.length < best_length) {
                    best_length = ant.length;
                    best_tour = ant.tour;
                }
            }
            UpdatePheromones(ants, best_tour, rho, Q);
            cout << "Iteration " << j + 1 << " Best length: " << best_length << "\n";
        }
        // best_tour.clear();
        // best_tour.push_back(0);
        // best_tour.push_back(21);
        // best_tour.push_back(27);
        // best_tour.push_back(30);
        // best_tour.push_back(25);
        // best_tour.push_back(7);
        // best_tour.push_back(47);
        // best_tour.push_back(5);
        // best_tour.push_back(22);
        // best_tour.push_back(6);
        // best_tour.push_back(42);
        // best_tour.push_back(23);
        // best_tour.push_back(13);
        // best_tour.push_back(24);
        // best_tour.push_back(12);
        // best_tour.push_back(40);
        // best_tour.push_back(39);
        // best_tour.push_back(18);
        // best_tour.push_back(41);
        // best_tour.push_back(43);
        // best_tour.push_back(16);
        // best_tour.push_back(3);
        // best_tour.push_back(17);
        // best_tour.push_back(46);
        // best_tour.push_back(11);
        // best_tour.push_back(36);
        // best_tour.push_back(14);
        // best_tour.push_back(44);
        // best_tour.push_back(32);
        // best_tour.push_back(38);
        // best_tour.push_back(9);
        // best_tour.push_back(48);
        // best_tour.push_back(8);
        // best_tour.push_back(29);
        // best_tour.push_back(33);
        // best_tour.push_back(49);
        // best_tour.push_back(15);
        // best_tour.push_back(20);
        // best_tour.push_back(28);
        // best_tour.push_back(19);
        // best_tour.push_back(34);
        // best_tour.push_back(35);
        // best_tour.push_back(2);
        // best_tour.push_back(1);
        // best_tour.push_back(10);
        // best_tour.push_back(37);
        // best_tour.push_back(4);
        // best_tour.push_back(45);
        // best_tour.push_back(50);
        // best_tour.push_back(26);
        // best_tour.push_back(31);

        // best_tour.push_back(0);
        // best_tour.push_back(21);
        // best_tour.push_back(7);
        // best_tour.push_back(25);
        // best_tour.push_back(30);
        // best_tour.push_back(27);
        // best_tour.push_back(2);
        // best_tour.push_back(35);
        // best_tour.push_back(34);
        // best_tour.push_back(19);
        // best_tour.push_back(1);
        // best_tour.push_back(28);
        // best_tour.push_back(20);
        // best_tour.push_back(15);
        // best_tour.push_back(49);
        // best_tour.push_back(33);
        // best_tour.push_back(29);
        // best_tour.push_back(8);
        // best_tour.push_back(48);
        // best_tour.push_back(9);
        // best_tour.push_back(38);
        // best_tour.push_back(32);
        // best_tour.push_back(44);
        // best_tour.push_back(14);
        // best_tour.push_back(43);
        // best_tour.push_back(41);
        // best_tour.push_back(18);
        // best_tour.push_back(39);
        // best_tour.push_back(40);
        // best_tour.push_back(12);
        // best_tour.push_back(24);
        // best_tour.push_back(13);
        // best_tour.push_back(23);
        // best_tour.push_back(42);
        // best_tour.push_back(6);
        // best_tour.push_back(22);
        // best_tour.push_back(47);
        // best_tour.push_back(5);
        // best_tour.push_back(26);
        // best_tour.push_back(50);
        // best_tour.push_back(45);
        // best_tour.push_back(11);
        // best_tour.push_back(46);
        // best_tour.push_back(17);
        // best_tour.push_back(3);
        // best_tour.push_back(16);
        // best_tour.push_back(36);
        // best_tour.push_back(4);
        // best_tour.push_back(37);
        // best_tour.push_back(10);
        // best_tour.push_back(31);
        best_length = ComputeTourLength(best_tour);

        cout << "Final best tour length: " << best_length << "\n";
        cout << "Tour: ";
        for (int city : best_tour) 
            cout << city + 1 << " ";
        cout << endl;

        ofstream outfile("best_path.txt");
        for (int i : best_tour){
            outfile << cities[i].id << " " << cities[i].x << " " << cities[i].y << "\n";
        }
        // 回到起點（形成封閉路徑）
        outfile << cities[best_tour[0]].id << " " << cities[best_tour[0]].x << " " << cities[best_tour[0]].y << "\n";
        outfile.close();
    }
}

void Alg::LoadCities(const string& filename){
    ifstream fin(filename);
    int id;
    City c;
    while (fin >> id >> c.x >> c.y) {
        c.id = id;
        cities.push_back(c);
    }
    num_cities = cities.size();
}

void Alg::ComputeDistances(){
    distance.resize(num_cities, vector<double>(num_cities, 0));
    pheromone.resize(num_cities, vector<double>(num_cities, default_pheromone));
    for (int i = 0; i < num_cities; ++i){
        for (int j = 0; j < num_cities; ++j){
            double dx = cities[i].x - cities[j].x;
            double dy = cities[i].y - cities[j].y;
            // distance[i][j] = sqrt(dx * dx + dy * dy);
            // distance[i][j] = int(sqrt(dx * dx + dy * dy) + 0.5);
            distance[i][j] = round(sqrt(dx * dx + dy * dy));                // 根據TSPLIB 95裡面定義的距離算法
            // distance[i][j] = ceil(sqrt(dx * dx + dy * dy));
            // distance[i][j] = floor(sqrt(dx * dx + dy * dy));
        }
    }
}

double Alg::ComputeTourLength(const vector<int>& tour){
    double length = 0.0;
    for (size_t i = 0; i < tour.size(); ++i){
        int from = tour[i];
        int to = tour[(i + 1) % tour.size()];
        length += distance[from][to];
    }
    return length;
}

int Alg::SelectNextCity(const vector<bool>& visited, int current_city, double alpha, double beta){
    vector<double> prob(num_cities, 0.0);
    double sum = 0.0;
    for (int i = 0; i < num_cities; ++i){
        if (!visited[i]){
            prob[i] = pow(pheromone[current_city][i], alpha) * pow(1.0 / distance[current_city][i], beta);
            sum += prob[i];
        }
    }

    uniform_real_distribution<> dist(0.0, 1.0);
    default_random_engine gen(random_device{}());
    double r = dist(gen), cumulative = 0.0;

    for (int i = 0; i < num_cities; ++i){
        if (!visited[i]){
            cumulative += prob[i] / sum;
            if (r <= cumulative)
                return i;
        }
    }

    for (int i = 0; i < num_cities; ++i)
        if (!visited[i]) 
            return i;
    return -1;
}

void Alg::UpdatePheromones(const vector<ant>& ants, const vector<int>& best_tour, double rho, double Q){
    for (auto& row : pheromone)
        for (auto& p : row)
            p *= (1.0 - rho);

    for (const auto& ant : ants){
        for (size_t i = 0; i < ant.tour.size(); ++i){
            int from = ant.tour[i];
            int to = ant.tour[(i + 1) % ant.tour.size()];
            double delta = Q / ant.length;
            pheromone[from][to] += delta;
            pheromone[to][from] += delta;
        }
    }

    // τ_max 與 τ_min
    double tau_max = 5.0;
    double tau_min = 0.3;

    // 限制所有費洛蒙在 τ_min ~ τ_max 之間
    for (int i = 0; i < num_cities; ++i){
        for (int j = 0; j < num_cities; ++j) {
            if (pheromone[i][j] > tau_max) pheromone[i][j] = tau_max;
            if (pheromone[i][j] < tau_min) pheromone[i][j] = tau_min;
        }
    }

    // 獎勵全局最佳路徑的費洛蒙
    double best_length = ComputeTourLength(best_tour);
    for (size_t i = 0; i < best_tour.size(); ++i){
        int from = best_tour[i];
        int to = best_tour[(i + 1) % best_tour.size()];
        double delta = Q / best_length;
        pheromone[from][to] += delta;
        pheromone[to][from] += delta;
    }

    // 每 pheromone_reset_period 代對非最優路徑的費洛蒙進行重置。
    generation_counter++;
    if (generation_counter % pheromone_reset_period == 0) {
        for (int i = 0; i < num_cities; ++i) {
            for (int j = 0; j < num_cities; ++j) {
                if (!IsEdgeInTour(i, j, best_tour)) {
                    pheromone[i][j] = 0.5;
                }
            }
        }
    }
}

bool Alg::IsEdgeInTour(int from, int to, const vector<int>& tour){
    for (size_t i = 0; i < tour.size(); ++i){
        int a = tour[i];
        int b = tour[(i + 1) % tour.size()];
        if ((a == from && b == to) || (a == to && b == from))
            return true;
    }
    return false;
}

double Alg::Distance(const City& a, const City& b){
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double Alg::TourLength(const std::vector<int>& tour, const std::vector<City>& cities){
    double total = 0.0;
    for (size_t i = 0; i < tour.size() - 1; ++i){
        total += Distance(cities[tour[i]], cities[tour[i+1]]);
    }
    total += Distance(cities[tour.back()], cities[tour[0]]);            // 加連回起點之長度
    return total;
}

void Alg::TwoOpt(std::vector<int>& tour, const std::vector<City>& cities){
    int total = tour.size();

    for (int i = 0; i < total; ++i) {
        for (int j = total - 1; j > i; --j){
            int i_pre = (i - 1 + total) % total;
            int j_next = (j + 1) % total;

            if (i_pre == j)     // 兩段相鄰，不需要反轉
                continue;

            int i_no = tour[i];
            int i_pre_no = tour[i_pre];
            int j_no = tour[j];
            int j_next_no = tour[j_next];

            double len1 = Distance(cities[i_pre_no], cities[i_no]) + Distance(cities[j_no], cities[j_next_no]);
            double len2 = Distance(cities[i_pre_no], cities[j_no]) + Distance(cities[i_no], cities[j_next_no]);

            if (len2 < len1){
                int start = i, end = j;
                while (start < end){
                    std::swap(tour[start], tour[end]);
                    ++start;
                    --end;
                }
            }
        }
    }
}

void Alg::Mutate(std::vector<int>& tour, double pmut){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);
    uniform_int_distribution<> idx(0, tour.size() - 1);

    if (dis(gen) < pmut){
        int i = idx(gen);
        int j = idx(gen);
        if (i != j)
            std::swap(tour[i], tour[j]);
    }
}
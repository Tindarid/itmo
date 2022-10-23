#include <algorithm>
#include <cstdio>
#include <cmath>
#include <vector>
#include <random>

using std::vector;
using std::pair;
using std::abs;

using vec = vector<int>;
using rvec = const vector<int> &;
using vecd = vector<double>;
using rvecd = const vector<double> &;
using matrix = vector<vec>;
using rmatrix = const vector<vec> &;
using matrixd = vector<vecd>;
using rmatrixd = const vector<vecd> &;
using minmax = vector<pair<double, double>>;

void add(vecd &to, rvecd from) {
    for (size_t i = 0; i < to.size(); ++i) {
        to[i] += from[i];
    }
}

int sign(double a) {
    return (a > 0) - (a < 0);
}

double scalar(rvecd w, rvecd a) {
    double sum = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        sum += w[i] * a[i];
    }
    return sum + w.back();
}

double smape(rvecd w, rvecd o, double t) {
    double y = scalar(w, o);
    return abs(y - t) / (abs(y) + abs(t));
}

double full_smape(rvecd w, rmatrixd objects, rvecd targets) {
    double ans = 0.0;
    for (size_t i = 0; i < objects.size(); ++i) {
        ans += smape(w, objects[i], targets[i]);
    }
    return ans / objects.size();
}

vecd gradient(rvecd w, rvecd a, int t) {
    vecd ans;
    ans.reserve(a.size());

    double f = scalar(w, a);
    double tt = abs(f) + abs(t) + 0.001;
    double temp = (sign(f - t) - sign(f) * abs(f - t) / tt) / tt;
    for (auto x : a) {
        ans.push_back(x * temp);
    }
    ans.push_back(temp);
    return ans;
}

vecd batched_gradient(rvecd w, rmatrixd objects, rvecd targets, rvec slices) {
    vecd ans;
    ans.resize(w.size(), 0.0);

    for (auto i : slices) {
        add(ans, gradient(w, objects[i], targets[i]));
    }

    for (auto &g : ans) {
        g /= slices.size();
    }
    return ans;
}

vecd full_gradient(rvecd w, rmatrixd objects, rvecd targets) {
    vecd ans;
    ans.resize(w.size(), 0.0);

    size_t total = objects.size();
    for (size_t i = 0; i < total; ++i) {
        add(ans, gradient(w, objects[i], targets[i]));
    }

    for (auto &g : ans) {
        g /= total;
    }
    return ans;
}

minmax normalize(matrixd &objects) {
    minmax MM;
    MM.resize(objects[0].size());

    for (size_t i = 0; i < objects.size(); ++i) {
        for (size_t j = 0; j < objects[i].size(); ++j) {
            if (i == 0) {
                MM[j].first = objects[i][j];
                MM[j].second = objects[i][j];
            } else {
                MM[j].first = std::min(objects[i][j], MM[j].first);
                MM[j].second = std::max(objects[i][j], MM[j].second);
            }
        }
    }

    for (size_t i = 0; i < objects.size(); ++i) {
        for (size_t j = 0; j < objects[i].size(); ++j) {
            if (MM[j].first == MM[j].second) {
                MM[j].first = MM[j].second / 2;
            }
            objects[i][j] = (objects[i][j] - MM[j].first) / (MM[j].second - MM[j].first);
        }
    }

    return MM;
}

pair<double, double> normalize_targets(vecd &targets) {
    pair<double, double> MM = {*std::min_element(targets.begin(), targets.end()), *std::max_element(targets.begin(), targets.end())};
    if (MM.first == MM.second) {
        MM.first = MM.second / 2;
    }
    for (size_t i = 0; i < targets.size(); ++i) {
        targets[i] = (targets[i] - MM.first) / (MM.second - MM.first);
    }
    return MM;
}

void denormalize(vecd &w, const minmax &MM) {
    vecd new_w(w.size());
    for (size_t i = 0; i < w.size() - 1; ++i) {
        new_w[i] = w[i] / (MM[i].second - MM[i].first);
    }
    for (size_t i = 0; i < w.size() - 1; ++i) {
        new_w.back() -= w[i] * MM[i].first / (MM[i].second - MM[i].first);
    }
    new_w.back() += w.back();
    w = std::move(new_w);
}

void denormalize_with_targets(vecd &w, const minmax &MM, pair<double,double> MM2) {
    vecd new_w(w.size());
    for (size_t i = 0; i < w.size() - 1; ++i) {
        new_w[i] = w[i] / (MM[i].second - MM[i].first);
    }
    for (size_t i = 0; i < w.size() - 1; ++i) {
        new_w.back() -= w[i] * MM[i].first / (MM[i].second - MM[i].first);
    }
    new_w.back() += w.back();
    for (size_t i = 0; i < w.size(); ++i) {
        new_w[i] *= (MM2.second - MM2.first);
    }
    new_w.back() += MM2.first;
    w = std::move(new_w);
}

double get_rate(rvecd grad, rvecd w, rvecd o, double t) {
    double temp = scalar(grad, o);

    if (temp == 0) {
        return 0;
    } else {
        return (scalar(w, o) - t) / temp / 2;
    }
}

double get_batched_rate(rvecd grad, rvecd w, rmatrixd objects, rvecd targets, rvec slices) {
    double ans = 0.0;

    for (auto i : slices) {
        ans += get_rate(grad, w, objects[i], targets[i]);
    }

    return ans / slices.size();
}

vector<double> sto_grad_descent(rmatrixd objects, rvecd targets) {
    size_t M = objects[0].size() + 1;
    size_t total = objects.size();
    double eps = 0.0001;

    vecd best;
    double best_Q = 1.0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-1.0 / (2 * M), 1.0 / (2 * M));

    for (int round = 0; round < 100; ++round) {
        vecd w, new_w;
        w.resize(M);

        for (size_t j = 0; j < M; ++j) {
            w[j] = dis(gen);
        }
        //double Q = full_smape(w, objects, targets);
        double s;

        for (int j = 0; j < 100 and ((j == 0 or s > eps)); j++) {
            //size_t ind = gen() % total;
            //auto g = gradient(w, objects[ind], targets[ind]);
            //double rate = get_rate(g, w, objects[ind], targets[ind]);

            int batch_size = 1;
            vec slices;
            for (int i = 0; i < batch_size; ++i) {
                slices.push_back(gen() % total);
            }
            auto g = batched_gradient(w, objects, targets, slices);
            double rate = get_batched_rate(g, w, objects, targets, slices);

            //double p = smape(w, objects[ind], targets[ind]);
            //Q = rate * p + (1 - rate) * Q;

            new_w.resize(M);
            for (size_t i = 0; i < w.size(); ++i) {
                new_w[i] = w[i] - g[i] * rate;
            }

            s = 0.0;
            for (size_t i = 0; i < w.size(); ++i) {
                s += abs(w[i] - new_w[i]);
            }
            w = std::move(new_w);
        }

        double Q = full_smape(w, objects, targets);

        if (round == 0 or Q < best_Q) {
            best = std::move(w);
            best_Q = Q;
        }
    }

    return best;
}

pair<matrixd, vecd> get_matrix_from_stdin() {
    int N; scanf("%d", &N);
    int M; scanf("%d", &M);

    matrixd objects(N);
    vecd targets(N);
    for (int i = 0; i < N; ++i) {
        objects[i].resize(M);

        int temp;
        for (int j = 0; j < M; ++j) {
            scanf("%d", &temp);
            objects[i][j] = temp;
        }
        scanf("%d", &temp);
        targets[i] = temp;
    }

    return {objects, targets};
}

pair<matrixd, vecd> get_matrix_from_file(FILE *f, int M) {
    int N; fscanf(f, "%d", &N);

    matrixd objects(N);
    vecd targets(N);
    for (int i = 0; i < N; ++i) {
        objects[i].resize(M);

        int temp;
        for (int j = 0; j < M; ++j) {
            fscanf(f, "%d", &temp);
            objects[i][j] = temp;
        }
        fscanf(f, "%d", &temp);
        targets[i] = temp;
    }

    return {objects, targets};
}

void print_ans(const vecd &ans) {
    for (auto i : ans) {
        printf("%f\n", i);
    }
}

pair<double, double> run_test(const char *path_to_file) {
    FILE *f = fopen(path_to_file, "r");

    int M; fscanf(f, "%d", &M);
    auto train_objects = get_matrix_from_file(f, M);
    auto test_objects = get_matrix_from_file(f, M);

    fclose(f);

    auto MM = normalize(train_objects.first);
    //auto MM2 = normalize_targets(train_objects.second);
    auto ans = sto_grad_descent(train_objects.first, train_objects.second);
    //printf("TEST: %s\n", path_to_file);
    double smape_on_train = full_smape(ans, train_objects.first, train_objects.second);
    //printf("SMAPE_ON_TRAIN: %f\n", smape_on_train);
    //denormalize_with_targets(ans, MM, MM2);
    denormalize(ans, MM);
    double smape_on_test = full_smape(ans, test_objects.first, test_objects.second);
    //printf("SMAPE_ON_TEST: %f\n", smape_on_test);
    return {smape_on_train, smape_on_test};
}

void run_tests() {
    vector<pair<double, double>> result;
    result.push_back(run_test("/home/nursan/ml/CF/D_input/0.40_0.65.txt"));
    result.push_back(run_test("/home/nursan/ml/CF/D_input/0.42_0.63.txt"));
    result.push_back(run_test("/home/nursan/ml/CF/D_input/0.48_0.68.txt"));
    result.push_back(run_test("/home/nursan/ml/CF/D_input/0.52_0.70.txt"));
    result.push_back(run_test("/home/nursan/ml/CF/D_input/0.57_0.79.txt"));
    result.push_back(run_test("/home/nursan/ml/CF/D_input/0.60_0.73.txt"));
    result.push_back(run_test("/home/nursan/ml/CF/D_input/0.60_0.80.txt"));
    result.push_back(run_test("/home/nursan/ml/CF/D_input/0.62_0.80.txt"));

    pair<double, double> res;
    for (auto i : result) {
        res.first += i.first, res.second += i.second;
    }
    res.first /= result.size();
    res.second /= result.size();
    printf("%f %f\n", res.first, res.second);
}

void CFsol() {
    auto train_objects = get_matrix_from_stdin();
    if (train_objects.first[0].size() != 1) {
      auto MM = normalize(train_objects.first);
      //auto MM2 = normalize_targets(train_objects.second);
      auto ans = sto_grad_descent(train_objects.first, train_objects.second);
      denormalize(ans, MM);
      print_ans(ans);
    } else {
        vecd x, y = train_objects.second;
        for (const auto &i : train_objects.first) {
            x.push_back(i[0]);
        }
        double avg_x = 0.0, avg_y = 0.0;
        for (size_t i = 0; i < x.size(); ++i) {
            avg_x += x[i], avg_y += y[i];
        }
        avg_x /= x.size(); avg_y /= y.size();

        double b0, b1 = 0.0, some = 0.0;
        for (size_t i = 0; i < x.size(); ++i) {
            b1 += (avg_x - x[i]) * (avg_y - y[i]);
            some += (avg_x - x[i]) * (avg_x - x[i]);
        }
        b1 /= some;
        b0 = avg_y - b1 * avg_x;

        printf("%f\n%f\n", b1, b0);
    }
}

int main() {
    run_tests();
    //CFsol();
}

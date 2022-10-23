#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <ctime>
#include <iomanip>
#include <cassert>
using namespace std;

using vecd = vector<long double>;
using rvecd = const vector<long double> &;

vector<vector<long long>> K;
vector<long long> Y;
long long C;

void in() {
  int N; cin >> N;
  K.resize(N); Y.resize(N);

  for (int i = 0; i < N; ++i) {
    K[i].resize(N);
    for (int j = 0; j < N; ++j) {
      cin >> K[i][j];
    }
    cin >> Y[i];
  }

  cin >> C;
}

void out(rvecd ans) {
  cout << fixed << setprecision(20);
  for (auto i : ans) {
    cout << i << "\n";
  }
}

void out_debug(rvecd ans) {
  cout << fixed << setprecision(20);
  for (auto i : ans) {
    cout << i << " ";
  }
  cout << endl;
}

long double count_without_b(rvecd ans, int i) {
  long double a = 0.0;
  for (size_t j = 0; j < K.size(); ++j) {
    a += K[j][i] * Y[j] * ans[j];
  }
  return a;
}

void out_stat(rvecd ans) {
  size_t good = 0;
  for (size_t i = 0; i < K.size(); ++i) {
    long double a = ans.back() + count_without_b(ans, i);
    if (a * Y[i] > 0) {
      good++;
    }
  }
  cout << "good: " << good << ", bad: " << K.size() - good << endl;
}

inline long double f(size_t ind, rvecd lambda, long double b) {
  for (size_t i = 0; i < K.size(); ++i) {
    b += lambda[i] * Y[i] * K[ind][i];
  }
  return b;
}

inline std::pair<long double, long double> LH(size_t i, size_t j, rvecd l) {
  if (Y[i] != Y[j]) {
    return {max(0.0L, l[j] - l[i]), min(static_cast<long double>(C), C + l[j] - l[i])};
  } else {
    return {max(0.0L, l[j] + l[i] - C), min(static_cast<long double>(C), l[j] + l[i])};
  }
}

inline long double count_for_b(long double b1, long double b2, size_t i, size_t j, rvecd l) {
  if (0 < l[j] and l[j] < C) {
    return b1;
  } else if (0 < l[i] and l[i] < C) {
    return b2;
  } else {
    return (b1 + b2) / 2;
  }
}

vecd sol() {
  constexpr long double EPS = 1e-16;
  constexpr int max_passes = 55000;
  int passes = 0;

  size_t N = K.size();
  vecd lambda(N);
  long double b = 0.0;

  srand(time(nullptr));
  while (passes < max_passes) {
    int changed_alphas = 0;

    long double E_i, E_j, l_i_old, l_j_old, L, H, eta, diff_j, diff_i, clipped_j, b1, b2;
    for (size_t i = 0, j; i < N; ++i) {
      E_i = f(i, lambda, b) - Y[i];

      if (!((Y[i] * E_i < -EPS and lambda[i] < C) or (Y[i] * E_i > EPS and lambda[i] > 0))) {
        continue;
      }

      j = (i + (rand() % (N - 1)) + 1 % N) % N;
      E_j = f(j, lambda, b) - Y[j];

      l_i_old = lambda[i], l_j_old = lambda[j];

      auto LH_ = LH(i, j, lambda);
      L = LH_.first, H = LH_.second;
      if (H - L < EPS) {
        continue;
      }

      eta = 2 * K[i][j] - K[i][i] - K[j][j];
      if (eta + EPS > 0) {
        continue;
      }

      lambda[j] = min(H, max(L, lambda[j] - Y[j] * (E_i - E_j) / eta));
      diff_j = l_j_old - lambda[j];

      lambda[i] += Y[i] * Y[j] * diff_j;
      diff_i = l_i_old - lambda[i];

      diff_j *= -1;
      diff_i *= -1;

      b1 = b - E_i - Y[i] * diff_i * K[i][i] - Y[j] * diff_j * K[i][j];
      b2 = b - E_j - Y[i] * diff_i * K[i][j] - Y[j] * diff_j * K[j][j];
      b = count_for_b(b1, b2, i, j, lambda);

      changed_alphas++;
    }

    changed_alphas = 0;
    if (!changed_alphas) {
      passes++;
    } else {
      passes = 0;
    }
  }

  lambda.push_back(b);
  return lambda;
}

int main() {
  in();
  auto s = sol();
  // out_debug(s);
  // out_stat(s);
  out(s);
}

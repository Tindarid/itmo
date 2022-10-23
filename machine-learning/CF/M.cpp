#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
using namespace std;
 
int main() {
  long long N; cin >> N;
  std::vector<std::pair<int, int>> x(N), y(N);
  std::vector<double> rank_x(N), rank_y(N);
  for (int i = 0; i < N; ++i) {
    cin >> x[i].first >> y[i].first;
    x[i].second = y[i].second = i;
  }
 
  std::sort(x.begin(), x.end());
  std::sort(y.begin(), y.end());
 
  for (int i = 0; i < N; ++i) {
    rank_x[x[i].second] = i;
    rank_y[y[i].second] = i;
  }
 
  double r = 0.0;
  for (int i = 0; i < N; ++i) {
    double a = rank_x[i] - rank_y[i];
    r += a * a;
  }
 
  r = 1.0L - (6.0L * r) / (N * (N * N - 1));
 
  cout << setprecision(10) << fixed << r << endl;
}

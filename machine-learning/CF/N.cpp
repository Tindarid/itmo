#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
using namespace std;

long long count_abs(std::vector<long long> &v) {
  std::sort(v.begin(), v.end());

  long long sum = 0;
  for (auto s : v) {
    sum += s;
  }

  long long ans = 0;
  for (int i = v.size() - 1; i >= 0; --i) {
    sum -= v[i];
    ans += i * v[i] - sum;
  }
  return ans;
}

int main() {
  int K, N;
  cin >> K >> N;
  std::vector<std::vector<long long>> Y(K);
  std::vector<long long> all(N);

  for (int i = 0, y, x; i < N; ++i) {
    cin >> x >> y;
    all[i] = x;
    Y[y - 1].push_back(x);
  }

  long long total = count_abs(all);
  long long inner = 0;
  for (int i = 0; i < K; ++i) {
    inner += count_abs(Y[i]);
  }

  cout << 2 * inner << endl;
  cout << 2 * (total - inner) << endl;
}

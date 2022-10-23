#include <iostream>
#include <vector>
#include <functional>
#include <iomanip>
#include <cmath>
using namespace std;

using ld = long double;

ld sum(const std::vector<ld> &d, std::function<ld(ld)> f) {
  ld ans = 0.0;
  for (auto i : d) {
    ans += f(i);
  }
  return ans;
}

ld sum2(const std::vector<ld> &d1, const std::vector<ld> &d2, std::function<ld(ld, ld)> f) {
  ld ans = 0.0;
  for (size_t i = 0; i < d1.size(); ++i) {
    ans += f(d1[i], d2[i]);
  }
  return ans;
}

int main() {
  int N; cin >> N;
  std::vector<ld> x(N), y(N);
  for (int i = 0; i < N; ++i) {
    cin >> x[i] >> y[i];
  }

  ld avg_x = sum(x, [](ld i) -> ld { return i; }) / x.size();
  ld avg_y = sum(y, [](ld i) -> ld { return i; }) / y.size();
  ld s1 = sum(x, [avg_x](ld i) -> ld { return (i - avg_x) * (i - avg_x); });
  ld s2 = sum(y, [avg_y](ld i) -> ld { return (i - avg_y) * (i - avg_y); });
  ld cov = sum2(x, y, [avg_x, avg_y](ld i, ld j) -> ld { return (i - avg_x) * (j - avg_y); });

  ld r;
  if (fabs(s1 - 0.0L) < 1e-6) {
    r = 0.0L;
  } else if (fabs(s2 - 0.0L) < 1e-6) {
    r = 0.0L;
  } else {
    r = cov / sqrt(s1 * s2);
  }
  cout << setprecision(6) << fixed << r;
}

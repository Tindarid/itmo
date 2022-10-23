#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  int fa, fb;
  for (int i = 0; i < m; ++i) {
    int from, to;
    scanf("%d %d", &from, &to);
    from--, to--;
    if (i == 0) {
      fa = from, fb = to;
    }
  }

  int q = 2 * (n - 2);
  printf("%d\n", q);
  fflush(stdout);

  vector<pair<int, int>> ans;
  ans.push_back({fa, 0});
  ans.push_back({fb, 1});

  for (int i = 0; i < n; ++i) {
    if (i == fa or i == fb) {
      continue;
    }

    int a, b, ans1, ans2, ans3, ans4;
    b = i + 1;

    a = fa + 1;
    printf("%d %d\n", a, b);
    fflush(stdout);
    scanf("%d %d", &ans1, &ans2);

    a = fb + 1;
    printf("%d %d\n", a, b);
    fflush(stdout);
    scanf("%d %d", &ans3, &ans4);

    if (ans1 == ans2) {
      ans.push_back({i, 0});
    } else if (ans3 == ans4) {
      ans.push_back({i, 1});
    } else {
      ans.push_back({i, 2});
    }
  }

  sort(ans.begin(), ans.end());

  for (const auto &p : ans) {
    printf("%d ", p.second);
  }
  printf("\n");
  fflush(stdout);

  return 0;
}

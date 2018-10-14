/**
 *    author: nthoang
 *    created: 14.10.2018
 *    judge: local
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...) 42
#endif

int main() {
  freopen("landscape.in", "r", stdin);
  freopen("landscape.out", "w", stdout);
  int n, x, y, z;
  scanf("%d %d %d %d", &n, &x, &y, &z);
  vector<int> a, b;
  for (int i = 0; i < n; ++i) {
    for (int t = 0; t < 2; ++t) {
      auto& v = t == 0 ? a : b;
      int d;
      scanf("%d", &d);
      while (d--) {
        v.push_back(i);
      }
    }
  }
  int na = (int) a.size(), nb = (int) b.size();
  vector<vector<int>> f(na + 1, vector<int>(nb + 1));
  for (int j = 1; j <= nb; ++j) {
    f[0][j] = x * j;
  }
  for (int i = 1; i <= na; ++i) {
    f[i][0] = y * i;
  }
  for (int i = 1; i <= na; ++i) {
    for (int j = 1; j <= nb; ++j) {
      f[i][j] = min(f[i][j - 1] + x, f[i - 1][j] + y);
      f[i][j] = min(f[i][j], f[i - 1][j - 1] + z * abs(a[i - 1] - b[j - 1]));
    }
  }
  printf("%d\n", f[na][nb]);
  return 0;
}
/**
 *    author: nthoang
 *    created: 15.10.2018
 *    judge: https://wcipeg.com/problem/coci061p5
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...) 42
#endif

int main() {
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int n;
  scanf("%d", &n);
  vector<vector<double>> a(n, vector<double>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int x;
      scanf("%d", &x);
      a[i][j] = 1.0 * x / 100;
    }
  }
  vector<double> f(1 << n);
  f[0] = 1.0;
  for (int mask = 0; mask < (1 << n); ++mask) {
    for (int i = 0; i < n; ++i) {
      if (mask >> i & 1) {
        continue;
      }
      int id = __builtin_popcount(mask);
      f[mask | (1 << i)] = max(f[mask | (1 << i)], f[mask] * a[id][i]);
    }
  }
  printf("%.6f\n", f.back() * 100);
  return 0;
}

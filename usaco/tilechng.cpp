/**
 *    author: nthoang
 *    created: 06.10.2019
 *    judge: local
**/
#include <bits/stdc++.h>

using namespace std;

const int inf = (int) 1e9;

int main() {
  freopen("tilechng.in", "r", stdin);
  freopen("tilechng.out", "w", stdout);
  int n, m;
  scanf("%d %d", &n, &m);
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  vector<vector<int>> f(2, vector<int>(m + 1, inf));
  f[0][0] = 0;
  for (int it = 0; it < n; ++it) {
    int i = it & 1;
    for (int s = 0; s <= m; ++s) {
      if (f[i][s] == inf) {
        continue;
      }
      for (int b = 0; b <= 100; ++b) {
        if (s + b * b > m) {
          continue;
        }
        f[(i + 1) & 1][s + b * b] = min(f[(i + 1) & 1][s + b * b], f[i][s] + (a[it] - b) * (a[it] - b));
      }
    }
    for (int j = 0; j <= m; ++j) {
      f[i][j] = inf;
    }
  }
  int ans = f[n & 1][m];
  printf("%d\n", ans == inf ? -1 : ans);
  return 0;
}


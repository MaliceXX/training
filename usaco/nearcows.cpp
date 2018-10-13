/**
 *    author: nthoang
 *    created: 13.10.2018
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
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int n, k;
  scanf("%d %d", &n, &k); 
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    --x; --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  vector<vector<int>> f(3, vector<int>(n));
  for (int i = 0; i < n; ++i) {
    scanf("%d", &f[0][i]);
  }
  for (int i = 0; i < n; ++i) {
    f[1][i] = f[0][i];
    for (int j : g[i]) {
      f[1][i] += f[0][j];
    }
  }
  for (int it = 2; it <= k; ++it) {
    f[it % 3].assign(n, 0);
    for (int i = 0; i < n; ++i) {
      for (int j : g[i]) {
        f[it % 3][i] += f[(it - 1) % 3][j];
      }
      f[it % 3][i] -= ((int) g[i].size() - 1) * f[(it - 2) % 3][i];
    }
  }
  for (int i = 0; i < n; ++i) {
    printf("%d\n", f[k % 3][i]);
  }
  return 0;
}
/**
 *    author: nthoang
 *    created: 12.10.2018
 *    judge: local
**/
#include <bits/stdc++.h>

using namespace std;

const int md = (int) 1e9 + 7;

int main() {
  freopen("alliance.in", "r", stdin);
  freopen("alliance.out", "w", stdout);
  int n, m;
  scanf("%d %d", &n, &m);
  vector<vector<int>> g(n);
  for (int i = 0; i < m; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    --x; --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  int ans = 1;
  vector<bool> was(n);
  for (int i = 0; i < n; ++i) {
    if (was[i]) {
      continue;
    }
    function<pair<int, int>(int)> dfs = [&](int v) {
      was[v] = true;
      pair<int, int> ret(1, (int) g[v].size());
      for (int to : g[v]) {
        if (!was[to]) {
          auto z = dfs(to);
          ret.first += z.first;
          ret.second += z.second;
        }
      }
      return ret;
    };
    auto z = dfs(i);
    z.second >>= 1;
    if (z.first < z.second) {
      ans = 0;
      break;
    } else if (z.first == z.second) {
      ans = (ans + ans) % md;
    } else {
      assert(z.first == z.second + 1);
      ans = (ans * 1LL * z.first) % md;
    }
  }
  printf("%d\n", ans);
  return 0;
}

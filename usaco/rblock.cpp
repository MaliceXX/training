/**
 *    author: nthoang
 *    created: 29.08.2018
 *    judge: local
**/
#include <bits/stdc++.h>

using namespace std;

const int inf = (int) 1e9;

int main() {
  freopen("rblock.in", "r", stdin);
  freopen("rblock.out", "w", stdout);
  int n, m;
  scanf("%d %d", &n, &m);
  vector<vector<pair<int, int>>> g(n);
  for (int i = 0; i < m; ++i) {
    int x, y, c;
    scanf("%d %d %d", &x, &y, &c);
    --x; --y;
    g[x].emplace_back(y, c);
    g[y].emplace_back(x, c);
  }
  int ans = 0;
  auto dijkstra = [&]() {
    vector<int> d(n, inf);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    d[0] = 0;
    pq.emplace(d[0], 0);
    while (!pq.empty()) {
      auto cur = pq.top();
      pq.pop();
      int v = cur.second;
      int expected = cur.first;
      if (d[v] != expected) {
        continue;
      }
      if (v == n - 1) {
        return d[v];
      }
      for (const auto& e : g[v]) {
        int to = e.first;
        if (d[to] > d[v] + e.second) {
          d[to] = d[v] + e.second;
          pq.emplace(d[to], to);
        }
      }
    }
    return 0;
  };
  int normal = dijkstra();
  for (int v = 0; v < n; ++v) {
    for (auto& e : g[v]) {
      e.second <<= 1;
      ans = max(ans, dijkstra());
      e.second >>= 1;
    }
  }
  printf("%d\n", ans - normal);
  return 0;
}

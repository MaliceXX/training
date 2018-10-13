/**
 *    author: nthoang
 *    created: 30.09.2018
 *    judge: local
**/
#include <bits/stdc++.h>

using namespace std;

const int inf = (int) 1e9;

int main() {
  freopen("relocate.in", "r", stdin);
  freopen("relocate.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<pair<int, int>>> g(n);
  vector<int> market(k);
  for (int i = 0; i < k; ++i) {
    cin >> market[i];
    --market[i];
  }
  for (int i = 0; i < m; ++i) {
    int x, y, c;
    cin >> x >> y >> c;
    --x; --y;
    g[x].emplace_back(y, c);
    g[y].emplace_back(x, c);
  }
  auto dijkstra = [&](int src) {
    vector<int> dist(n, inf);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[src] = 0;
    pq.emplace(dist[src], src);
    while (!pq.empty()) {
      auto cur = pq.top();
      pq.pop();
      int v = cur.second;
      int expected = cur.first;
      if (dist[v] != expected) {
        continue;
      }
      for (auto e : g[v]) {
        int to = e.first;
        int cost = e.second;
        if (dist[to] > dist[v] + cost) {
          dist[to] = dist[v] + cost;
          pq.emplace(dist[to], to);
        }
      }
    }
    return dist;
  };
  vector<vector<int>> d(k);
  for (int i = 0; i < k; ++i) {
    d[i] = dijkstra(market[i]);
  }
  int ans = inf;
  vector<int> p(k);
  iota(p.begin(), p.end(), 0);
  do {
    for (int i = 0; i < n; ++i) {
      if (find(market.begin(), market.end(), i) != market.end()) {
        continue;
      }
      int total = d[p[0]][i];
      for (int j = 0; j < k - 1; ++j) {
        total += d[p[j]][market[p[j + 1]]];
      }
      total += d[p[k - 1]][i];
      ans = min(ans, total);
    }
  } while (next_permutation(p.begin(), p.end()));
  cout << ans << '\n';
  return 0;
}

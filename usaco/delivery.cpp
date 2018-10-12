/**
 *    author: nthoang
 *    created: 02.09.2018
 *    judge: local
**/
#include <bits/stdc++.h>

using namespace std;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};
const int inf = (int) 1e9;

struct point {
  int x;
  int y;

  inline bool operator<(const point& other) const {
    return x < other.x || (x == other.x && y < other.y);
  }

  inline bool operator!=(const point& other) const {
    return x != other.x || y != other.y;
  }
};

int main() {
  freopen("delivery.in", "r", stdin);
  freopen("delivery.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<point> p(n);
  set<point> se;
  for (int i = 0; i < n; ++i) {
    cin >> p[i].x >> p[i].y;
    se.insert(p[i]);
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 4; ++j) {
      point pp = {p[i].x + dx[j], p[i].y + dy[j]};
      if (!se.count(pp)) {
        p.push_back(pp);
      }
    }
  }
  int sz = (int) p.size();
  auto inside = [](point a, point b, point c) {
    if (a.x == b.x) {
      return c.x == a.x && min(a.y, b.y) < c.y && c.y < max(a.y, b.y);
    } else {
      return c.y == a.y && min(a.x, b.x) < c.x && c.x < max(a.x, b.x);
    }
  };
  auto valid = [&](point a, point b) {
    bool ret = false;
    for (int id = 0; id < 2; ++id) {
      ret |= (a.x == b.x || a.y == b.y || !se.count(id == 0 ? point{a.x, b.y} : point{b.x, a.y}));
      for (int i = 0; i < n; ++i) {
        if (id == 0 && (inside({a.x, a.y}, {a.x, b.y}, p[i]) 
                     || inside({a.x, b.y}, {b.x, b.y}, p[i]))) {
          ret = false;
        }
        if (id == 1 && (inside({a.x, a.y}, {b.x, a.y}, p[i]) 
                     || inside({b.x, a.y}, {b.x, b.y}, p[i]))) {
          ret = false;
        }
      }
    }
    return ret;
  };
  vector<vector<pair<int, int>>> g(sz);
  for (int i = 0; i < sz; ++i) {
    for (int j = 0; j < sz; ++j) {
      if (valid(p[i], p[j])) {
        g[i].emplace_back(j, abs(p[i].x - p[j].x) + abs(p[i].y - p[j].y));
      }
    }
  }
  int ans = 0;
  for (int src = 0; src < n; ++src) {
    vector<int> d(sz, inf);
    d[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(d[src], src);
    while (!pq.empty()) {
      auto cur = pq.top();
      pq.pop();
      int v = cur.second;
      int expected = cur.first;
      if (expected != d[v]) {
        continue;
      }
      for (auto e : g[v]) {
        int to = e.first;
        int cost = e.second;
        if (d[to] > d[v] + cost) {
          d[to] = d[v] + cost;
          if (to >= n) {
            pq.emplace(d[to], to);  
          }
        }
      }
    }
    if (d[(src + 1) % n] == inf) {
      cout << -1 << '\n';
      return 0;
    } else {
      ans += d[(src + 1) % n];
    }
  }
  cout << ans << '\n';
  return 0;
}

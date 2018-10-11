/**
 *    author: nthoang
 *    created: 29.08.2018
 *    judge: local
**/
#include <bits/stdc++.h>

using namespace std;

class segtree {
 public:
  int n;
  vector<int> add;
  vector<int> tree;

  inline void push(int x, int l, int r) {
    if (add[x] != 0) {
      tree[x] += add[x] * (r - l + 1);
      if (l != r) {
        add[x + x] += add[x];
        add[x + x + 1] += add[x];
      }
      add[x] = 0;
    }
  }

  segtree(int n) : n(n) {
    add.resize(4 * n);
    tree.resize(4 * n);
  }

  void modify(int x, int l, int r, int ll, int rr, int v) {
    push(x, l, r);
    if (r < ll || rr < l) {
      return;
    }
    if (ll <= l && r <= rr) {
      add[x] += v;
      push(x, l, r);
      return;
    }
    int y = (l + r) >> 1;
    modify(x + x, l, y, ll, rr, v);
    modify(x + x + 1, y + 1, r, ll, rr, v);
    tree[x] = tree[x + x] + tree[x + x + 1];
  }

  int get(int x, int l, int r, int ll, int rr) {
    push(x, l, r);
    if (r < ll || rr < l) {
      return 0;
    }
    if (ll <= l && r <= rr) {
      return tree[x];
    }
    int y = (l + r) >> 1;
    return get(x + x, l, y, ll, rr) + get(x + x + 1, y + 1, r, ll, rr);
  }
};

int main() {
  freopen("grassplant.inp", "r", stdin);
  freopen("grassplant.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, tt;
  cin >> n >> tt;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int x, y;
    cin >> x >> y;
    --x; --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  vector<int> pv(n, -1);
  vector<int> depth(n, -1);
  vector<int> sz(n);
  vector<int> pos(n, -1);
  vector<int> order;
  function<void(int)> dfs = [&](int v) {
    pos[v] = (int) order.size();
    order.push_back(v);
    sz[v] = 1;
    for (int to : g[v]) {
      if (to == pv[v]) {
        continue;
      }
      pv[to] = v;
      depth[to] = depth[v] + 1;
      dfs(to);
      sz[v] += sz[to];
    }
  };
  for (int tries = 0; tries < 2; ++tries) {
    order.clear();
    depth.assign(n, -1);
    for (int i = n - 1; i >= 0; --i) {
      if (depth[i] == -1) {
        dfs(i);
      }
    }
    if (tries == 1) {
      break;
    }
    for (int i = 0; i < n; ++i) {
      if (g[i].empty()) {
        continue;
      }
      int best = -1, bid = 0;
      for (int j = 0; j < (int) g[i].size(); ++j) {
        int v = g[i][j];
        if (sz[v] > best) {
          best = sz[v];
          bid = j;
        }
      }
      swap(g[i][0], g[i][bid]);
    }
  }
  vector<int> head(n);
  iota(head.begin(), head.end(), 0);
  for (int i = 0; i < n - 1; ++i) {
    int x = order[i];
    int y = order[i + 1];
    if (pv[y] == x) {
      head[y] = head[x];
    }
  }
  vector<vector<int>> pr(n, vector<int>(20, -1));
  for (int i = 0; i < n; ++i) {
    pr[i][0] = pv[i];
  }
  for (int i = 1; i < 20; ++i) {
    for (int v = 0; v < n; ++v) {
      if (pr[v][i - 1] != -1) {
        pr[v][i] = pr[pr[v][i - 1]][i - 1];
      }
    }
  }
  auto lca = [&](int x, int y) {
    if (depth[x] < depth[y]) {
      swap(x, y);
    }
    for (int i = 19; i >= 0; --i) {
      if (depth[x] - (1 << i) >= depth[y]) {
        x = pr[x][i];
      }
    }
    if (x == y) {
      return x;
    }
    for (int i = 19; i >= 0; --i) {
      if (pr[x][i] != -1 && pr[x][i] != pr[y][i]) {
        x = pr[x][i];
        y = pr[y][i];
      }
    }
    return pv[x];
  };
  vector<vector<int>> ls(n);
  for (int i = 0; i < n; ++i) {
    for (int j : g[i]) {
      if (j != pv[i]) {
        ls[i].push_back(j);
      }
    }
  }
  segtree st(n);
  while (tt--) {
    char c;
    int x, y;
    cin >> c >> x >> y;
    --x; --y;
    int z = lca(x, y);
    long long ans = 0;
    for (int id = 0; id < 2; ++id) {
      int v = id == 0 ? x : y;
      if (v == z) {
        continue;
      }
      int w = -1, lo = 0, hi = (int) ls[z].size() - 1;
      while (lo <= hi) {
        int mi = (lo + hi) >> 1;
        if (mi == (int) ls[z].size() - 1
            || (pos[ls[z][mi]] <= pos[v] && pos[v] < pos[ls[z][mi + 1]])) {
          w = ls[z][mi]; 
          break;
        }
        if (pos[v] < pos[ls[z][mi]]) {
          hi = mi - 1;
        } else {
          lo = mi + 1;
        }
      }
      assert(w != -1);
      while (true) {
        int u = depth[head[v]] > depth[w] ? head[v] : w;
        if (c == 'P') {
          st.modify(1, 0, n - 1, pos[u], pos[v], 1);
        } else {
          ans += st.get(1, 0, n - 1, pos[u], pos[v]);
        }
        if (u == w) {
          break;
        } else {
          v = pv[u];
        }
      }
    }
    if (c == 'Q') {
      cout << ans << '\n';
    }
  }
  return 0;
}

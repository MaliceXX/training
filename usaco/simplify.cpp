#include <bits/stdc++.h>

using namespace std;

const int md = (int) 1e9 + 7;

class dsu {
 public:
  int n;
  vector<int> p;
  
  dsu(int n) : n(n) {
    p.resize(n);
    iota(p.begin(), p.end(), 0);
  }
  
  int get(int x) {
    return x == p[x] ? x : p[x] = get(p[x]);
  }
  
  inline bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x != y) {
      p[x] = y;
      return true;
    }
    return false;
  }
};

int main() {
  freopen("simplify.in", "r", stdin);
  freopen("simplify.out", "w", stdout);
  int n, m;
  scanf("%d %d", &n, &m);
  vector<tuple<int, int, int>> edges(m);
  for (int i = 0; i < m; ++i) {
    int x, y, c;
    scanf("%d %d %d", &x, &y, &c);
    --x; --y;
    edges[i] = make_tuple(c, x, y);
  }
  sort(edges.begin(), edges.end());
  dsu ds(n);
  int ans = 1;
  long long sum = 0;
  for (int i = 0; i < m; ) {
    int j = i;
    set<pair<int, int>> type_of_union;
    int can_be_used = 0;
    while (j < m && get<0>(edges[j]) == get<0>(edges[i])) {
      int x = get<1>(edges[j]);
      int y = get<2>(edges[j]);
      x = ds.get(x);
      y = ds.get(y);
      if (x > y) {
        swap(x, y);
      }
      if (x != y) {
        type_of_union.insert(make_pair(x, y));
        ++can_be_used;
      }
      ++j;
    }
    int used = 0;
    for (; i < j; ++i) {
      used += ds.unite(get<1>(edges[i]), get<2>(edges[i]));
    }
    sum += 1LL * get<0>(edges[i - 1]) * used;
    if (can_be_used == 2) {
      if (used == 1) {
        ans = (ans + ans) % md;
      }
    }
    if (can_be_used == 3) {
      if (used == 1 || (used == 2 && (int) type_of_union.size() == 3)) {
        ans = (ans * 3LL) % md;
      }
      if (used == 2 && (int) type_of_union.size() == 2) {
        ans = (ans + ans) % md;
      }
    }
  }
  printf("%lld %d", sum, ans);
  return 0;
}


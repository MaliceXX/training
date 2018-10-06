/**
 *    author: nthoang
 *    created: 06.10.2018
 *    judge: local
**/
#include <bits/stdc++.h>

using namespace std;

template <typename T>
class fenwick {
 public:
  int n;
  vector<T> fenw;
  
  fenwick(int n) : n(n) {
    fenw.resize(n);
  }
  
  void modify(int x, T v) {
    while (x < n) {
      fenw[x] += v;
      x |= (x + 1);
    }
  }
  
  T get(int x) {
    T v{};
    while (x >= 0) {
      v += fenw[x];
      x = (x & (x + 1)) - 1;
    }
    return v;
  }
};

int main() {
  freopen("median.in", "r", stdin);
  freopen("median.out", "w", stdout);
  int n, x;
  scanf("%d %d", &n, &x);
  vector<int> h(n);
  set<int> se;
  se.insert(0);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &h[i]);
    h[i] = h[i] >= x ? 1 : -1;
    if (i > 0) {
      h[i] += h[i - 1];
    }
    se.insert(h[i]);
  }
  vector<int> vals(se.begin(), se.end());
  auto pos = [&](int v) {
    return lower_bound(vals.begin(), vals.end(), v) - vals.begin();
  };
  fenwick<int> fenw(111111);
  long long ans = 0;
  fenw.modify(pos(0), 1);
  for (int i = 0; i < n; ++i) {
    ans += fenw.get(pos(h[i]));
    fenw.modify(pos(h[i]), 1);
  }
  printf("%lld\n", ans);
  return 0;
}


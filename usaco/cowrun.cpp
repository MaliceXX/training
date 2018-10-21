/**
 *    author: nthoang
 *    created: 21.10.2018
 *    judge: local
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...) 42
#endif

enum {
  top,
  bottom
};

int main() {
  freopen("cowrun.in", "r", stdin);
  freopen("cowrun.out", "w", stdout);
  int n, m, k;
  scanf("%d %d %d", &n, &m, &k);
  char b[22];
  scanf("%s", b);
  vector<vector<int>> a(n);
  for (int i = 0; i < n; ++i) {
    a[i].resize(8);
    for (int j = 0; j < 8; ++j) {
      scanf("%d", &a[i][j]);
    }
  }
  auto calc = [&](int round, int pos, int fj, int bessie) {
    return (pos * 1LL * a[round][fj * 4 + bessie * 2] + pos + a[round][fj * 4 + bessie * 2 + 1]) % m;
  };
  function<bool(int, int, int, int)> solve = [&](int who, int round, int pos, int last) {
    if (round == n) {
      assert(who == 0);
      return pos <= k || pos + k >= m;
    }
    int which = rand() & 1;
    if (who == 1) {
      return solve(0, round + 1, calc(round, pos, last, which), which)
          && solve(0, round + 1, calc(round, pos, last, which ^ 1), which ^ 1);
    }
    return solve(1, round, pos, which) || solve(1, round, pos, which ^ 1);
  };
  int pos = 0;
  for (int i = 0; i < n; ++i) {
    if (solve(1, i, pos, bottom)) {
      putchar('B');
      pos = calc(i, pos, bottom, b[i] == 'B');
    } else {
      putchar('T');
      pos = calc(i, pos, top, b[i] == 'B');
    }
  }
  putchar('\n');
  return 0;
}

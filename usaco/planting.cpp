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
  freopen("planting.in", "r", stdin);
  freopen("planting.out", "w", stdout);
  int n;
  scanf("%d", &n);
  vector<int> all_x(2 * n);
  vector<int> x1(n), y1(n), x2(n), y2(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d %d %d %d", &x1[i], &y1[i], &x2[i], &y2[i]);
    all_x[i + i] = x1[i];
    all_x[i + i + 1] = x2[i];
  }
  sort(all_x.begin(), all_x.end());
  long long ans = 0;
  for (int i = 0; i < 2 * n; ) {
    vector<pair<int, int>> sweep;
    for (int j = 0; j < n; ++j) {
      if (x1[j] <= all_x[i] && all_x[i] < x2[j]) {
        sweep.emplace_back(y2[j], 1);
        sweep.emplace_back(y1[j], -1);
      }
    }
    sort(sweep.begin(), sweep.end());
    if (sweep.empty()) {
      ++i;
      continue;
    }
    int beg_x = all_x[i];
    while (i < 2 * n && all_x[i] == beg_x) {
      ++i;
    }
    int sum_x = all_x[i] - beg_x;
    int sum_y = 0, it = 0;
    while (it < (int) sweep.size()) {
      int beg_y = sweep[it].first;
      int cur = sweep[it++].second;
      while (it < (int) sweep.size() && cur != 0) {
        cur += sweep[it++].second;
      }
      sum_y += sweep[it - 1].first - beg_y;
    }
    ans += sum_x * 1LL * sum_y;
  }
  printf("%lld\n", ans);
  return 0;
}
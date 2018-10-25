/**
 *    author: nthoang
 *    created: 25.10.2018
 *    judge: local
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...) 42
#endif

const int N = 20;
const int inf = (int) 1e9;

int n, w;
int c[N];
pair<int, int> dp[1 << N];
int last[1 << N];

int main() {
  freopen("skyscraper.in", "r", stdin);
  freopen("skyscraper.out", "w", stdout);
  scanf("%d %d", &n, &w);
  for (int i = 0; i < n; ++i) {
    scanf("%d", c + i);
  }
  dp[0].first = 1;
  for (int mask = 1; mask < (1 << n); ++mask) {
    dp[mask] = make_pair(inf, inf);
    for (int i = 0; i < n; ++i) {
      if (mask >> i & 1) {
        auto pre = dp[mask ^ (1 << i)];
        if (pre.second + c[i] > w) {
          ++pre.first;
          pre.second = c[i];
        } else {
          pre.second += c[i];
        }
        if (dp[mask] > pre) {
          dp[mask] = pre;
          last[mask] = i;
        }
      }
    }
  }
  printf("%d\n", dp[(1 << n) - 1].first);
  int mask = (1 << n) - 1, sum = dp[mask].second;
  vector<int> v;
  while (mask > 0) {
    v.push_back(last[mask]);
    sum -= c[v.back()];
    mask ^= (1 << v.back());
    if (sum == 0) {
      printf("%d ", (int) v.size());
      for (int id : v) {
        printf("%d ", id + 1);
      }
      printf("\n");
      v.clear();
      sum = dp[mask].second;
    }
  }
  return 0;
}

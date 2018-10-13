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

const long long inf = (long long) 1e15;

int main() {
  freopen("coupons.in", "r", stdin);
  freopen("coupons.out", "w", stdout);
  int n, k;
  long long m;
  scanf("%d %d %lld", &n, &k, &m);
  vector<pair<int, int>> p(n), c(n);
  vector<int> revoke(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d %d", &p[i].first, &c[i].first);
    p[i].second = c[i].second = i;
    revoke[i] = p[i].first - c[i].first;
  }
  sort(p.begin(), p.end());
  sort(c.begin(), c.end());
  vector<bool> was(n);
  priority_queue<int, vector<int>, greater<int>> pq;
  for (int i = 0; i < k; ++i) {
    pq.push(0);
  }
  p.emplace_back(inf, -1);
  c.emplace_back(inf, -1);
  int ip = 0, ic = 0, ans = 0;
  long long cur = 0;
  while (true) {
    while (ip < n && was[p[ip].second]) {
      ++ip;
    }
    while (ic < n && was[c[ic].second]) {
      ++ic;
    }
    if (ip == n && ic == n) {
      break;
    }
    if (c[ic].first + pq.top() < p[ip].first) {
      cur += c[ic].first + pq.top();
      pq.pop();
      pq.push(revoke[c[ic].second]);
      was[c[ic++].second] = true;
    } else {
      cur += p[ip].first;
      was[p[ip++].second] = true;
    }
    if (cur <= m) {
      ++ans;
    } else {
      break;
    }
  }
  printf("%d\n", ans);
  return 0;
}
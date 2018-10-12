/**
 *    author: nthoang
 *    created: 02.09.2018
 *    judge: local
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  freopen("climb.in", "r", stdin);
  freopen("climb.out", "w", stdout);
  int n;
  scanf("%d", &n);
  vector<pair<int, int>> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d %d", &a[i].first, &a[i].second);
  }
  sort(a.begin(), a.end(), [](pair<int, int> p, pair<int, int> q) {
    if (p.first < p.second) {
      return q.first < q.second ? p.first < q.first : true;
    }
    return q.first > q.second ? p.second > q.second : false;
  });
  int ans = 0, cur = 0;
  for (int i = 0; i < n; ++i) {
    cur += a[i].first;
    ans = max(ans, cur);
    ans += a[i].second;
  }
  printf("%d\n", ans);
  return 0;
}

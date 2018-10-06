/**
 *    author: nthoang
 *    created: 06.10.2018 
 *    judge: local
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int n;
  scanf("%d", &n);
  vector<pair<int, int>> a(n);
  unordered_set<int> se;
  for (int i = 0; i < n; ++i) {
    scanf("%d %d", &a[i].first, &a[i].second);
    se.insert(a[i].second);
  }
  int m = (int) se.size();
  sort(a.begin(), a.end());
  int ans = (int) 1e9;
  unordered_map<int, int> mp;
  for (int l = 0, r = 0; l < n; ++l) {
    while (r < n && (int) mp.size() < m) {
      ++mp[a[r++].second];
    }
    if (r == n && (int) mp.size() < m) {
      break;
    }
    ans = min(ans, a[r - 1].first - a[l].first);
    --mp[a[l].second];
    if (mp[a[l].second] == 0) {
      mp.erase(a[l].second);
    }
  }
  printf("%d\n", ans);
  return 0;
}


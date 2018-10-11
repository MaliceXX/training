/**
 *    author: nthoang
 *    created: 29.08.2018
 *    judge: local
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  freopen("photo.in", "r", stdin);
  freopen("photo.out", "w", stdout);
  int n;
  scanf("%d", &n);
  vector<vector<int>> pos(5, vector<int>(n));
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < n; ++j) {
      int id;
      scanf("%d", &id);
      --id;
      pos[i][id] = j;
    }
  }
  vector<int> ans(n);
  iota(ans.begin(), ans.end(), 0);
  sort(ans.begin(), ans.end(), [&](int x, int y) {
    int cnt = 0;
    for (int i = 0; i < 5; ++i) {
      cnt += pos[i][x] < pos[i][y];
    }
    return cnt >= 3;
  });
  for (int i = 0; i < n; ++i) {
    printf("%d\n", ans[i] + 1);
  }
  return 0;
}

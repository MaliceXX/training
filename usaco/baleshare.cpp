/**
 *    author: nthoang
 *    created: 12.10.2018
 *    judge: local
**/

#include <bits/stdc++.h>

using namespace std;

int main() {
  freopen("baleshare.in", "r", stdin);
  freopen("baleshare.out", "w", stdout);
  int n;
  scanf("%d", &n);
  vector<vector<vector<bool>>> f(2);
  for (int i = 0; i < 2; ++i) {
    f[i].resize(2222);
    for (int j = 0; j < 2222; ++j) {
      f[i][j].resize(2222);
    }
  }
  f[0][0][0] = true;
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    int a;
    scanf("%d", &a);
    for (int x = 0; x <= sum; ++x) {
      for (int y = 0; y <= sum; ++y) {
        if (f[i & 1][x][y]) {
          f[(i + 1) & 1][x][y] = true;
          f[(i + 1) & 1][x + a][y] = true;
          f[(i + 1) & 1][x][y + a] = true;
        }
      }
    }
    sum += a;
  }
  int ans = -1;
  for (int x = 0; x <= sum; ++x) {
    for (int y = 0; y <= sum; ++y) {
      if (f[n & 1][x][y]) {
        int z = sum - x - y;
        int mx = max(x, max(y, z));
        ans = ans == -1 ? mx : min(ans, mx); 
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}

/**
 *    author: nthoang
 *    created: 26.10.2018
 *    judge: https://wcipeg.com/problem/coci061p6
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...) 42
#endif

const int N = 333;

char a[N][N];
int h[2][N][N];

int main() {
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%s", a[i]);
    for (int j = 0; j < m; ++j) {
      h[0][i][j] = (j == 0 ? 0 : h[0][i][j - 1]) + (a[i][j] == '1');
      h[1][i][j] = (i == 0 ? 0 : h[1][i - 1][j]) + (a[i][j] == '1');
    }
  }
  auto check = [&](int i, int j, int k) {
    for (int l = 0; l <= k / 2; ++l) {
      if (h[0][i + l][j + k - 1] - h[0][i + l][j - 1] !=
          h[0][i + k - l - 1][j + k - 1] - h[0][i + k - l - 1][j - 1]) {
        return false;      
      }
      if (h[1][i + k - 1][j + l] - h[1][i - 1][j + l] !=
          h[1][i + k - 1][j + k - l - 1] - h[1][i - 1][j + k - l - 1]) {
        return false;      
      }  
    }
    return true;
  };
  int ans = min(n, m);
  bool found = false;
  while (ans > 1) {
    for (int i = 0; i + ans <= n; ++i) {
      for (int j = 0; j + ans <= m; ++j) {
        if (check(i, j, ans)) {
          found = true;
        }
      }
    }
    if (found) {
      break;
    } else {
      --ans;
    }
  }
  printf("%d\n", ans == 1 ? -1 : ans);
  return 0;
}

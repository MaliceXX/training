/**
 *    author: nthoang
 *    created: 06.10.2018
 *    judge: local
**/
#include <bits/stdc++.h>

using namespace std;

const int N = 9;
const int inf = (int) 1e9;

int row[N];
int dp[N + 10][(1 << N) + 10][(1 << 3) + 10];

int solve(int i, int col, int sum) {
  if (i == 9) {
    return col == 0 && sum == 0 ? 0 : inf;
  }
  if (i % 3 == 0) {
    if (sum != 0) {
      return inf;
    }
  }
  int& res = dp[i][col][sum];
  if (res != -1) {
    return res;
  }
  res = inf;
  for (int mask = 0; mask < 1 << 9; ++mask) {
    if (__builtin_popcount(mask) & 1) {
      continue;
    }
    int ncol = col ^ mask;
    vector<int> s(3);
    for (int j = 0; j < 3; ++j) {
      s[j] = sum >> j & 1;
    }
    for (int j = 0; j < 9; ++j) {
      s[j / 3] ^= (mask >> j & 1);
    }
    int nsum = 0;
    for (int j = 0, p = 1; j < 3; ++j, p <<= 1) {
      nsum += s[j] * p;
    }
    res = min(res, __builtin_popcount(mask ^ row[i]) + solve(i + 1, ncol, nsum));
  }
  return res;
}

int main() {
  freopen("bsudoku.in", "r", stdin);
  freopen("bsudoku.out", "w", stdout);
  for (int i = 0; i < 9; ++i) {
    char s[9];
    scanf("%s", s);
    for (int j = 0, p = 1; j < 9; ++j, p <<= 1) {
      row[i] += p * (s[j] - '0');
    }
  }
  memset(dp, -1, sizeof(dp));
  printf("%d\n", solve(0, 0, 0));
  return 0;
}

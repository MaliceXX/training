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

const int BITS = 5555;
const int inf = (int) 1e7;

static int k;
static int dp[BITS][11][2];

int calc(int it, int on_bits, int significant) {
  if (it == BITS) {
    return significant && on_bits == k;
  }
  int& ret = dp[it][on_bits][significant];
  if (ret != -1) {
    return ret;
  }
  ret = 0;
  for (int i = 0; i < 2; ++i) {
    if (i == 1 && on_bits == k) {
      continue;
    }
    ret += calc(it + 1, on_bits + i, significant | i);
    ret = min(ret, inf);
  }
  return ret;
}

string solve(int it, int on_bits, int significant, int pos) {
  if (it == BITS) {
    assert(significant && on_bits == k && pos == 1);
    return "";
  }
  int sz = calc(it + 1, on_bits, significant);
  if (pos <= sz) {
    return "0" + solve(it + 1, on_bits, significant, pos);
  }
  assert(on_bits < k);
  return "1" + solve(it + 1, on_bits + 1, significant | 1, pos - sz);
}

int main() {
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int n;
  scanf("%d %d", &n, &k);
  if (k == 1) {
    putchar('1');
    for (int i = 0; i < n - 1; ++i) {
      putchar('0');
    }
    putchar('\n');
    return 0;
  }
  memset(dp, -1, sizeof(dp));
  string ans = solve(0, 0, 0, n);
  while (!ans.empty() && ans[0] == '0') {
    ans.erase(ans.begin());
  }
  printf("%s\n", ans.c_str());
  return 0;
}


#include <bits/stdc++.h>

using namespace std;

int main() {
  freopen("umbrella.in", "r", stdin);
  freopen("umbrella.out", "w", stdout);
  int n, m;
  scanf("%d %d", &n, &m);
  vector<int> x(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &x[i]);
  }
  sort(x.begin(), x.end());
  vector<int> cost(m + 1);
  for (int i = 1; i <= m; ++i) {
    scanf("%d", &cost[i]);
  }
  for (int i = m - 1; i >= 0; --i) {
    cost[i] = min(cost[i], cost[i + 1]);
  }
  vector<int> f(n + 1, numeric_limits<int>::max());
  f[n] = 0;
  for (int i = n - 1; i >= 0; --i) {
    for (int j = i; j < n; ++j) {
      f[i] = min(f[i], cost[x[j] - x[i] + 1] + f[j + 1]);
    }
  }
  printf("%d\n", f[0]);
  return 0;
}


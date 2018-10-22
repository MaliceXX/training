#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...) 42
#endif

inline long long sqr(int x) {
  return x * 1LL * x;
}

int main() {
  freopen("banner.in", "r", stdin);
  freopen("banner.out", "w", stdout);
  int n, m, L, H, md;
  scanf("%d %d %d %d %d", &n, &m, &L, &H, &md);
  if (md == 1) {
    puts("0");
    return 0;
  }
  vector<vector<int>> primes(n + 1);
  for (int i = 2; i <= n; ++i) {
    if (primes[i].empty()) {
      for (int j = i; j <= n; j += i) {
        primes[j].push_back(i);
      }
    }
  }
  auto calc = [&](int low, int high, int p) {
    long long l = (low + p - 1) / p;
    long long r = high / p;
    return ((m + 1) * (r - l + 1) - p * (r * (r + 1) - l * (l - 1)) / 2) % md;  
  };
  int ans = 0, mn = min(n, H);
  int low = L, high = min(m, H);
  for (int w = 1; w <= mn; ++w) {
    while (low > 1 && sqr(low - 1) + sqr(w) >= sqr(L)) {
      --low;
    }
    while (high > 0 && sqr(high) + sqr(w) > sqr(H)) {
      --high;
    }
    if (low > high || low > m) {
      continue;
    }
    int all = 1 << (int) primes[w].size();
    int cnt = 0;
    for (int mask = 0; mask < all; ++mask) {
      int p = 1, parity = 1;
      for (int i = 0; i < (int) primes[w].size(); ++i) {
        if (mask >> i & 1) {
          p *= primes[w][i];
          parity *= -1;
        }
      }
      cnt = (cnt + parity * calc(low, high, p)) % md;
    }
    ans = (ans + (n - w + 1) * 1LL * cnt) % md;
    if (ans < 0) {
      ans += md;
    } 
  }
  if (L <= 1 && 1 <= H) {
    ans = (ans + ans + (n + 1) * 1LL * m + (m + 1) * 1LL * n) % md;
  } else {
    ans = (ans + ans) % md;
  }
  printf("%d\n", ans);
  return 0;
}

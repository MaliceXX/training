/**
 *    author: nthoang
 *    created: 14.10.2018
 *    judge: local
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...) 42
#endif

int main() {
  freopen("fpot.in", "r", stdin);
  freopen("fpot.out", "w", stdout);
  int n, d;
  scanf("%d %d", &n, &d);
  vector<pair<int, int>> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d %d", &a[i].first, &a[i].second);
  }
  sort(a.begin(), a.end());
  vector<vector<int>> mn(n, vector<int>(20, -1));
  vector<vector<int>> mx(n, vector<int>(20, -1));
  for (int i = 0; i < n; ++i) {
    mn[i][0] = i;
    mx[i][0] = i;
  }
  for (int j = 1; j < 20; ++j) {
    for (int i = 0; i + (1 << j) - 1 < n; ++i) {
      for (int t = 0; t < 2; ++t) {
        int l = t == 0 ? mn[i][j - 1] : mx[i][j - 1];
        int r = t == 0 ? mn[i + (1 << (j - 1))][j - 1] : mx[i + (1 << (j - 1))][j - 1];
        if (t == 0) {
          mn[i][j] = a[l].second < a[r].second ? l : r;
        } else {
          mx[i][j] = a[l].second > a[r].second ? l : r;
        }
      }
    }
  }
  auto get = [&](int t, int l, int r) {
    const auto& v = t == 0 ? mn : mx;
    int lg = (int) log2(r - l + 1);
    int ll = v[l][lg];
    int rr = v[r - (1 << lg) + 1][lg];
    return t == 0 ? (a[ll].second < a[rr].second ? ll : rr) : (a[ll].second > a[rr].second ? ll : rr);
  };
  auto search = [&](int key) {
    int ret = -1, low = 0, high = n - 1;
    while (low <= high) {
      int mid = (low + high) >> 1;
      if (a[mid].first <= key) {
        ret = mid;
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }
    return ret;
  };
  auto check = [&](int w) {
    for (int i = 0; i < n; ++i) {
      int j = search(a[i].first + w);
      if (a[get(1, i, j)].second - a[get(0, i, j)].second >= d) {
        return true;
      }
      if (j == n - 1) {
        break;
      }
    }
    return false;
  };
  int ans = -1, low = 0, high = (int) 1e6;
  while (low <= high) {
    int mid = (low + high) >> 1;
    if (check(mid)) {
      ans = mid;
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  printf("%d\n", ans);
  return 0;
}
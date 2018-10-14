/**
 *    author: nthoang
 *    created: 14.10.2018
 *    judge: https://wcipeg.com/problem/coci061p1
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...) 42
#endif

int main() {
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  set<int> se;
  for (int i = 0; i < 10; ++i) {
    int x;
    scanf("%d", &x);
    se.insert(x % 42);
  }
  printf("%d\n", (int) se.size());
  return 0;
}

/**
 *    author: nthoang
 *    created: 14.10.2018
 *    judge: https://wcipeg.com/problem/coci061p2
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
  int r;
  scanf("%d", &r);
  printf("%.6f\n%.6f\n", 1.0 * r * r * acos(-1.0), 1.0 * r * r * 2);
  return 0;
}

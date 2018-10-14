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

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};
const int inf = (int) 1e9;

typedef tuple<int, int, int> pq_node;

int main() {
  freopen("tractor.in", "r", stdin);
  freopen("tractor.out", "w", stdout);
  int n, st_x, st_y;
  scanf("%d %d %d", &n, &st_x, &st_y);
  const int N = 1001;
  vector<vector<bool>> a(N + 1, vector<bool>(N + 1));
  for (int i = 0; i < n; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    a[x][y] = true;
  }
  priority_queue<pq_node, vector<pq_node>, greater<pq_node>> pq;
  vector<vector<int>> d(N + 1, vector<int>(N + 1, inf));
  d[st_x][st_y] = 0;
  pq.emplace(d[st_x][st_y], st_x, st_y);
  while (!pq.empty()) {
    int expected, x, y;
    tie(expected, x, y) = pq.top();
    pq.pop();
    if (expected != d[x][y]) {
      continue;
    }
    if (x == 0 && y == 0) {
      printf("%d\n", d[x][y]);
      return 0;
    }
    for (int i = 0; i < 4; ++i) {
      int xx = x + dx[i];
      int yy = y + dy[i];
      if (0 <= xx && xx <= N && 0 <= yy && yy <= N) {
        if (d[xx][yy] > d[x][y] + a[xx][yy]) {
          d[xx][yy] = d[x][y] + a[xx][yy];
          pq.emplace(d[xx][yy], xx, yy);
        }
      }
    }
  }
  assert(false);
  return 0;
}
/**
 *    author: nthoang
 *    created: 15.10.2018
 *    judge: https://wcipeg.com/problem/coci061p4
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

int main() {
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int n, m;
  scanf("%d %d", &n, &m);
  vector<string> a(n);
  for (int i = 0; i < n; ++i) {
    char foo[m];
    scanf("%s", foo);
    a[i] = foo;
  }
  queue<pair<int, int>> foo[2], bar[2];
  vector<vector<int>> d(n, vector<int>(m));
  vector<vector<bool>> was[2];
  for (int t = 0; t < 2; ++t) {
    was[t].resize(n, vector<bool>(m));
  }
  pair<int, int> st, fin;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (a[i][j] == '*') {
        foo[0].push(make_pair(i, j));
        was[0][i][j] = true;
      } else if (a[i][j] == 'S') {
        st = make_pair(i, j);
      } else if (a[i][j] == 'D') {
        fin = make_pair(i, j);
      }
    }
  }
  foo[1].push(st);
  was[1][st.first][st.second] = true;
  while (!foo[1].empty()) {
    for (int rot = 0; rot < 2; ++rot) {
      assert(bar[rot].empty());
      while (!foo[rot].empty()) {
        auto cur = foo[rot].front();
        foo[rot].pop();
        if (rot == 1 && cur == fin) {
          printf("%d\n", d[cur.first][cur.second]);
          return 0;
        }
        for (int i = 0; i < 4; ++i) {
          int x = cur.first + dx[i];
          int y = cur.second + dy[i];
          if (x < 0 || x >= n || y < 0 || y >= m || was[rot][x][y] || a[x][y] == 'X') {
            continue;
          }
          if (rot == 1 && was[0][x][y]) {
            continue;
          }
          if (rot == 0 && make_pair(x, y) == fin) {
            continue;
          }
          was[rot][x][y] = true;
          if (rot == 1) {
            d[x][y] = d[cur.first][cur.second] + 1;
          }
          bar[rot].push(make_pair(x, y));
        }
      }
      swap(foo[rot], bar[rot]);
    }
  }
  puts("KAKTUS");
  return 0;
}

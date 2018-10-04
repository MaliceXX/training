/**
 *    author: nthoang
 *    created: 04.10.2018
 *    judge: local
**/
#include <bits/stdc++.h>

using namespace std;

const int inf = (int) 1e9;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

int main() {
  freopen("pageant.in", "r", stdin);
  freopen("pageant.out", "w", stdout);
  int n, m;
  scanf("%d %d", &n, &m);
  vector<string> c(n);
  for (int i = 0; i < n; ++i) {
    char foo[55];
    scanf("%s", foo);
    c[i] = foo;
  }
  vector<vector<int>> a(n, vector<int>(m, -1));
  function<void(int, int, int)> dfs_label = [&](int i, int j, int v) {
    a[i][j] = v;
    for (int k = 0; k < 4; ++k) {
      int x = i + dx[k];
      int y = j + dy[k];
      if (0 <= x && x < n && 0 <= y && y < m && c[x][y] == 'X' && a[x][y] == -1) {
        dfs_label(x, y, v);
      }
    }
  };
  for (int i = 0, v = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (c[i][j] == 'X' && a[i][j] == -1) {
        dfs_label(i, j, v++);
      }
    }
  }
  auto bfs = [&](int src_x, int src_y) {
    vector<vector<bool>> was(n, vector<bool>(m));
    vector<vector<int>> d(n, vector<int>(m));
    vector<int> dist(3, -1);
    queue<pair<int, int>> qu;
    qu.push(make_pair(src_x, src_y));
    was[src_x][src_y] = true;
    while (!qu.empty()) {
      auto cur = qu.front();
      qu.pop();
      int x = cur.first;
      int y = cur.second;
      if (a[x][y] != -1 && dist[a[x][y]] == -1) {
        dist[a[x][y]] = d[x][y];
      }
      for (int i = 0; i < 4; ++i) {
        int xx = x + dx[i];
        int yy = y + dy[i];
        if (0 <= xx && xx < n && 0 <= yy && yy < m) {
          if (!was[xx][yy]) {
            was[xx][yy] = true;
            d[xx][yy] = d[x][y] + 1;
            qu.push(make_pair(xx, yy));
          }
        }
      }
    };
    return dist;
  };
  vector<vector<int>> min_dist(3, vector<int>(3, inf));
  int ans = inf;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      auto d = bfs(i, j);
      if (c[i][j] == '.') {
        ans = min(ans, d[0] + d[1] + d[2] - 2);  
      } else {
        int v = a[i][j];
        for (int k = 0; k < 3; ++k) {
          min_dist[v][k] = min(min_dist[v][k], d[k]);
        }
      }
    }
  }
  for (int i = 0; i < 3; ++i) {
    int sum = 0;
    for (int j = 0; j < 3; ++j) {
      sum += min_dist[i][j];
    }
    ans = min(ans, sum - 2);
  }
  printf("%d\n", ans);
  return 0;
}

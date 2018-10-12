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

template <typename T>
struct point2d {
  T x, y;
  point2d() : x(0), y(0) {}
  point2d(const T& x, const T& y) : x(x), y(y) {}
  point2d operator+(const point2d& p) { return point2d(x + p.x, y + p.y); }
  point2d operator-(const point2d& p) { return point2d(x - p.x, y - p.y); }
  point2d operator*(const T &a) { return point2d(x * a, y * a); }
  point2d operator/(const T &a) { return point2d(x / a, y / a); }
};

typedef point2d<long long> point;
typedef pair<point, point> segment;

inline void get(point& p) {
  scanf("%lld %lld", &p.x, &p.y);
}

inline void get(segment& s) {
  get(s.first); get(s.second);
}

inline long long dot(point a, point b) {
  return a.x * 1LL * b.x + a.y * 1LL * b.y;
}

inline long long cross(point a, point b) {
  return a.x * 1LL * b.y - b.x * 1LL * a.y;
}

inline long long norm(point a) {
  return dot(a, a);
}

inline int ccw(point a, point b, point c) {
  b = b - a; c = c - a;
  long long det = cross(b, c);
  if (det < 0) return -1;
  else if (det > 0) return 1;
  else if (dot(b, c) < 0) return -2;
  else if (norm(b) < norm(c)) return 2;
  else return 0;
}

inline bool intersect(point a, point b, point c, point d) {
  return ccw(a, b, c) * ccw(a, b, d) <= 0 && ccw(c, d, a) * ccw(c, d, b) <= 0;
}

int main() {
  freopen("steeple.in", "r", stdin);
  freopen("steeple.out", "w", stdout);
  int n;
  scanf("%d", &n);
  vector<segment> ver, hor;
  for (int i = 0; i < n; ++i) {
    segment s;
    get(s);
    if (s.first.x == s.second.x) {
      ver.push_back(s);
    } else {
      hor.push_back(s);
    }
  }
  int nv = (int) ver.size(), nh = hor.size();
  vector<vector<int>> g(nv);
  for (int i = 0; i < nv; ++i) {
    for (int j = 0; j < nh; ++j) {
      if (intersect(ver[i].first, ver[i].second, hor[j].first, hor[j].second)) {
        g[i].push_back(j);
      }
    }
  }
  vector<int> match(nh, -1);
  int max_matching = 0;
  for (int i = 0; i < nv; ++i) {
    vector<bool> was(nh);
    function<bool(int)> dfs = [&](int v) {
      for (int u : g[v]) {
        if (!was[u]) {
          was[u] = true;
          if (match[u] == -1 || dfs(match[u])) {
            match[u] = v;
            return true;
          }  
        }
      }
      return false;
    };
    max_matching += dfs(i);
  }
  printf("%d\n", n - max_matching);
  return 0;
}
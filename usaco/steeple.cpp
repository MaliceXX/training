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
  typedef T ftype;

  ftype x;
  ftype y;

  point2d() { }

  point2d(const ftype& _x, const ftype& _y) : x(_x), y(_y) { }

  point2d& operator+=(const point2d& p) {
    x += p.x; 
    y += p.y;
    return *this;
  }

  point2d& operator-=(const point2d& p) {
    x -= p.x; 
    y -= p.y;
    return *this;
  }

  point2d& operator*=(ftype k) {
    x *= k; 
    y *= k;
    return* this;
  }

  point2d& operator/=(ftype k) {
    x /= k;
    y /= k;
    return *this;
  }
};

typedef point2d<int> point;

inline long long dot(point p, point q) {
  return p.x * 1LL * q.x + p.y * 1LL * q.y;
}

inline long long norm(point p) {
  return dot(p, p);
}

inline long long cross(point p, point q) {
  return p.x * 1LL * q.y - q.x * 1LL * p.y;
}

inline int ccw(point a, point b, point c) {
  b -= a; c -= a;
  long long d = cross(b, c);
  if (d < 0) return -1;
  else if (d > 0) return 1;
  else if (dot(b, c) < 0) return -2;
  else if (norm(b) < norm(c)) return 2;
  return 0;
}

inline bool intersect(point a, point b, point c, point d) {
  return ccw(a, b, c) * ccw(a, b, d) <= 0 && ccw(c, d, a) * ccw(c, d, b) <= 0;
}

inline void get(point& p) {
  scanf("%d %d", &p.x, &p.y);
}

typedef pair<point, point> segment;

int main() {
  freopen("steeple.in", "r", stdin);
  freopen("steeple.out", "w", stdout);
  int n;
  scanf("%d", &n);
  vector<segment> ver, hor;
  for (int i = 0; i < n; ++i) {
    segment s;
    get(s.first);
    get(s.second);
    if (s.first.x == s.second.x) {
      ver.push_back(s);
    } else {
      hor.push_back(s);
    }
  }
  int nv = (int) ver.size();
  int nh = (int) hor.size();
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
      for (int to : g[v]) {
        if (!was[to]) {
          was[to] = true;
          if (match[to] == -1 || dfs(match[to])) {
            match[to] = v;
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

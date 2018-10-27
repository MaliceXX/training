/**
 *    author: nthoang
 *    created: 27.10.2018
 *    judge: local
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...) 42
#endif

inline int gcd(int a, int b) {
  while (b > 0) {
    int t = a % b;
    a = b;
    b = t;
  }
  return a;
}

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

struct line {
  int a, b, c;

  line() { }

  line(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { }

  line(const point& p, const point& q) {
    a = q.y - p.y;
    b = p.x - q.x;
    c = -a * p.x - b * p.y;
  }

  inline bool operator<(const line& l) const {
    return make_tuple(a, b, c) < make_tuple(l.a, l.b, l.c);
  }

  inline line canon() {
    int g = gcd(abs(a), gcd(abs(b), abs(c)));
    if (make_tuple(a, b, c) < make_tuple(0, 0, 0)) {
      g *= -1;
    }
    return line(a / g, b / g, c / g);
  }
};

inline line bisector(const point& p, const point& q) {
  int a = p.x - q.x;
  int b = p.y - q.y;
  int c = -a * (p.x + q.x) - b * (p.y + q.y);
  return line(a << 1, b << 1, c);
}

int main() {
  freopen("symmetry.in", "r", stdin);
  freopen("symmetry.out", "w", stdout);
  int n;
  scanf("%d", &n);
  vector<point> p(n);
  set<pair<int, int>> se;
  for (int i = 0; i < n; ++i) {
    scanf("%d %d", &p[i].x, &p[i].y);
    se.insert(make_pair(p[i].x, p[i].y));
  }
  set<line> ls;
  for (int i = 0; i < 2; ++i) {
    for (int j = i + 1; j < n; ++j) {
      ls.insert(line(p[i], p[j]).canon());
      ls.insert(bisector(p[i], p[j]).canon());
    }
  }
  int ans = 0;
  for ( auto& l : ls) {
    int a = l.a, b = l.b, c = l.c;
    bool ok = true;
    for (int i = 0; i < n; ++i) {
      long long t = -2LL * b * c - 2LL * a * b * p[i].x + (a * a - b * b) * 1LL * p[i].y;
      assert(a * a + b * b != 0);
      if (t % (a * a + b * b) != 0) {
        ok = false;
        break;
      }
      int y = t / (a * a + b * b), x;
      if (a == 0) {
        x = p[i].x;
      } else if ((-2 * c - b * y - b * p[i].y - a * p[i].x) % a != 0) {
        ok = false;
        break;
      } else {
        x = (-2 * c - b * y - b * p[i].y - a * p[i].x) / a;
      }
      if (!se.count(make_pair(x, y))) {
        ok = false;
        break;
      }
    }
    ans += ok;
  }
  printf("%d\n", ans);
  return 0;
}

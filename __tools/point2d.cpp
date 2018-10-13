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

/**
 *    author: nthoang
 *    created: 15.10.2018
 *    judge: https://wcipeg.com/problem/coci061p3
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...) 42
#endif

struct frame {
  vector<vector<char>> c;
    
  frame(int type, char center) {
    c.resize(5);
    for (int i = 0; i < 5; ++i) {
      c[i].assign(5, '.');
    }
    char ch = type == 0 ? '#' : '*';
    c[0][2] = c[1][1] = c[1][3] = c[2][0] = ch;
    c[2][4] = c[3][1] = c[3][3] = c[4][2] = ch;
    c[2][2] = center;
  }
  
  inline frame operator+=(const frame& other) {
    char last = *c[2].rbegin();
    if (last == '#' && other.c[2][0] == '*') {
      c[2][(int) c[2].size() - 1] = '*';
    }
    for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 4; ++j) {
        c[i].push_back(other.c[i][j + 1]);
      }
    }
    return *this;
  }
};

int main() {
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  char s[22];
  scanf("%s", s);
  frame a(0, s[0]);
  int len = strlen(s);
  for (int i = 1; i < len; ++i) {
    a += frame(i % 3 == 2, s[i]);
  }
  for (int i = 0; i < 5; ++i) {
    for (char c : a.c[i]) {
      putchar(c);
    }
    putchar('\n');
  }
  return 0;
}

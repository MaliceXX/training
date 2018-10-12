/**
 *    author: nthoang
 *    created: 02.09.2018
 *    judge: local
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  freopen("combos.in", "r", stdin);
  freopen("combos.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(0);
  int m, n;
  cin >> m >> n;
  vector<string> s(m);
  vector<vector<vector<int>>> next(m);
  for (int i = 0; i < m; ++i) {
    cin >> s[i];
    next[i].resize(s[i].size() + 1);
    for (int j = 0; j <= (int) s[i].size(); ++j) {
      next[i][j].resize(3);
      for (int k = 0; k < 3; ++k) {
        string t(s[i].begin(), s[i].begin() + j);
        t.push_back(k + 'A');
        while (t.size() > s[i].size()) {
          t.erase(t.begin());
        }
        while (true) {
          bool match = true;
          for (int it = 0; it < (int) t.size(); ++it) {
            match &= (t[it] == s[i][it]);
            if (!match) {
              break;
            }
          }
          if (match) {
            next[i][j][k] = (int) t.size();
            break;
          } else {
            t.erase(t.begin());
          }
        }
      }
    }
  }
  vector<map<vector<int>, int>> dp(n);
  function<int(int, vector<int>)> solve = [&](int it, vector<int> match) {
    if (it == n) {
      return 0;
    }
    if (dp[it].count(match)) {
      return dp[it][match];
    }
    int& ret = dp[it][match];
    int add = 0;
    for (int i = 0; i < m; ++i) {
      add += (match[i] == (int) s[i].size());
    }
    for (int c = 0; c < 3; ++c) {
      auto n_match = match;
      assert((int) n_match.size() == m);
      for (int i = 0; i < m; ++i) {
        assert(match[i] <= (int) s[i].size());
        n_match[i] = next[i][match[i]][c];
      }
      ret = max(ret, add + solve(it + 1, n_match));
    }
    return ret;
  }; 
  int ans = 0;
  for (int c = 0; c < 3; ++c) {
    vector<int> v(m);
    for (int i = 0; i < m; ++i) {
      v[i] = next[i][0][c];
    }
    ans = max(ans, solve(0, v));
  }
  cout << ans << '\n';
  return 0;
}

class hopcroft_karp {
 public:
  int na, nb;
  vector<int> pa, pb;
  vector<vector<int>> g;
  vector<int> d;
  
  hopcroft_karp(int _na, int _nb) : na(_na), nb(_nb) {
    pa.resize(na);
    pb.resize(nb);
    g.resize(na);
    d.resize(na);
  }
  
  inline void add_edge(int a, int b) {
    g[a].push_back(b);
  }
  
  void bfs() {
    fill(d.begin(), d.end(), -1);
    queue<int> qu;
    for (int i = 0; i < na; ++i) {
      if (pa[i] == -1) {
        d[i] = 0;
        qu.push(i);
      }
    }
    while (!qu.empty()) {
      int v = qu.front();
      qu.pop();
      for (int to : g[v]) {
        int u = pb[to];
        if (d[u] == -1) {
          d[u] = d[v] + 1;
          qu.push(u);
        }
      }
    }
  }
  
  bool dfs(int v) {
    for (int to : g[v]) {
      int u = pb[to];
      if (u == -1 || (d[u] == d[v] + 1 && dfs(u))) {
        pa[v] = to;
        pb[to] = v;
        return true;
      }
    }
    return false;
  }
  
  int max_matching() {
    fill(pa.begin(), pa.end(), -1);
    fill(pb.begin(), pb.end(), -1);
    int ret = 0;
    while (true) {
      bfs();
      int add = 0;
      for (int i = 0; i < na; ++i) {
        if (pa[i] == -1 && dfs(i)) {
          ++add;
        }
      }
      ret += add;
      if (add == 0) {
        break;
      }
    }
    return ret;
  }
};

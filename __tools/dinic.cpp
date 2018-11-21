template <typename T>
class dinic {
 public:
  struct edge {
    int from;
    int to;
    T cap;
    T flow;
  };
  
  int n;
  int st, fin;
  vector<edge> edges;
  vector<vector<int>> g;
  vector<int> level;
  vector<int> ptr;
  
  dinic(int _n, int _st, int _fin) : n(_n), st(_st), fin(_fin) {
    g.resize(n);
    level.resize(n);
    ptr.resize(n);
  }
  
  void add_edge(int x, int y, T c) {
    int id = (int) edges.size();
    edges.push_back({x, y, c, 0});
    edges.push_back({y, x, 0, 0});
    g[x].push_back(id);
    g[y].push_back(id + 1);
  }
  
  bool bfs() {
    fill(level.begin(), level.end(), -1);
    level[st] = 0;
    queue<int> qu;
    qu.push(st);
    while (!qu.empty()) { 
      int v = qu.front();
      qu.pop();
      for (int id : g[v]) {
        const auto& e = edges[id];
        int to = e.to;
        if (e.cap - e.flow < 1 || level[to] != -1) {
          continue;
        }
        level[to] = level[v] + 1;
        qu.push(to);
      }
    }
    return level[fin] != -1;
  }
  
  T dfs(int v, T pushed) {
    if (pushed == 0) {
      return 0;
    }
    if (v == fin) {
      return pushed;
    }
    for (int& cid = ptr[v]; cid < (int) g[v].size(); ++cid) {
      int id = g[v][cid];
      int to = edges[id].to;
      if (level[to] != level[v] + 1 || edges[id].cap - edges[id].flow < 1) {
        continue;
      }
      T t = dfs(to, min(pushed, edges[id].cap - edges[id].flow));
      if (t == 0) {
        continue;
      }
      edges[id].flow += t;
      edges[id ^ 1].flow -= t;
      return t;
    }
    return 0;
  }
  
  T max_flow() {
    T flow = 0;
    while (bfs()) {
      fill(ptr.begin(), ptr.end(), 0);
      while (T pushed = dfs(st, numeric_limits<T>::max())) {
        flow += pushed;
      }
    }
    return flow;
  }
};

#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define X first  // X means cost
#define Y second // Y means index

int V, E, st; // number of veticies, number of edges, start vertex
int table[20005] = {0};
int pre[20005] = {0};
const int INF = 0x3f3f3f3f;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> V >> E >> st;
  vector<vector<pair<int, int>>> edges(V + 1);
  for (int i = 0; i < E; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    edges[u].push_back({c, v});
  }
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;
  for (int i = 1; i <= V; i++) {
    table[i] = INF;
  }
  pq.push({0, st});
  table[st] = 0;
  while (!pq.empty()) {
    auto cur = pq.top();
    pq.pop();
    if (cur.X != table[cur.Y])
      continue;
    for (auto nxt : edges[cur.Y]) {
      if (table[cur.Y] + nxt.X < table[nxt.Y]) {
        table[nxt.Y] = cur.X + nxt.X;
        pq.push({table[nxt.Y], nxt.Y});
        pre[nxt.Y] = cur.Y;
      }
    }
  }
  for (int i = 1; i <= V; i++) {
    if (table[i] == INF) {
      cout << "INF\n";
    } else {
      cout << table[i] << "\n";
    }
  }
}
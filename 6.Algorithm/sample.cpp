#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
const int INF = 0x3f3f3f3f;
int table[20005];
int inverse_table[20005];
bool done[20005] = {false};
bool isIn[20005] = {false};
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int N, M, X; // number of verticies, number of edges, start vertex
  cin >> N >> M >> X;
  vector<vector<pair<int, int>>> edges(N + 1);
  vector<vector<pair<int, int>>> inverse_edges(N + 1);
  // "edges[i]" means outgoing edges list of i
  // first element of the pair means the other end of the edge,
  // second element of the pair means cost of the edge
  for (int i = 0; i < M; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    edges[a].push_back({b, c});
    inverse_edges[b].push_back({a, c});
  }
  for (int i = 1; i <= N; i++) {
    table[i] = INF;
    inverse_table[i] = INF;
  }
  table[X] = 0;
  priority_queue<int, vector<int>, greater<int>> q;
  q.push(X);
  isIn[X] = true;
  while (!q.empty()) {
    int next = q.top();
    q.pop();
    for (int j = 0; j < edges[next].size(); j++) {
      int en = edges[next][j].first;
      int cost = edges[next][j].second;
      table[en] = min(table[en], table[next] + cost);
      if (!isIn[en]) {
        if (!done[en]) {
          q.push(en);
        }
      }
    }
  }
  for (int i = 1; i <= N; i++) {
    if (table[i] == INF) {
      cout << "INF\n";
    } else {
      cout << table[i] << "\n";
    }
  }
}
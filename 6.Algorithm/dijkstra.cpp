#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
const int INF = 0x3f3f3f3f;
int table[20005];
bool done[20005] = {false};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int N, M, X; // number of verticies, number of edges, start vertex
  cin >> N >> M >> X;
  vector<vector<pair<int, int>>> edges(N + 1);
  // "edges[i]" means outgoing edges list of i
  // first element of the pair means the other end of the edge,
  // second element of the pair means cost of the edge
  for (int i = 0; i < M; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    edges[a].push_back({b, c});
  }
  for (int i = 1; i <= N; i++) {
    table[i] = INF;
  }
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      q;
  q.push({0, X});
  table[X] = 0;
  while (!q.empty()) {
    int dist = q.top().first;
    int next = q.top().second;
    q.pop();
    if (done[next])
      continue;
    done[next] = true;
    for (int j = 0; j < edges[next].size(); j++) {
      int en = edges[next][j].first;
      int cost = edges[next][j].second;
      if (table[en] > dist + cost) {
        table[en] = dist + cost;
        q.push({table[en], en});
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
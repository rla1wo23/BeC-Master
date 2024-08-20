#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
const int INF = 0x3f3f3f3f;
int table[1005];
int inverse_table[1005];
bool done[1005] = {false};
bool inverse_done[1005] = {false};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int N, M, X;
  cin >> N >> M >> X;
  vector<vector<pair<int, int>>> edges(N + 1);
  vector<vector<pair<int, int>>> inverse_edges(N + 1);

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
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      q;
  q.push({0, X});
  while (!q.empty()) {
    int dist = q.top().first;
    int next = q.top().second;
    q.pop();
    if (done[next])
      continue;
    done[next] = true;
    for (int i = 0; i < edges[next].size(); i++) {
      int adj = edges[next][i].first;
      int cost = edges[next][i].second;
      if (table[adj] > cost + dist) {
        table[adj] = cost + dist;
        q.push({table[adj], adj});
      }
    }
  }
  inverse_table[X] = 0;
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      rq;
  rq.push({0, X});
  while (!rq.empty()) {
    int dist = rq.top().first;
    int next = rq.top().second;
    rq.pop();
    if (inverse_done[next])
      continue;
    done[next] = true;
    for (int i = 0; i < inverse_edges[next].size(); i++) {
      int adj = inverse_edges[next][i].first;
      int cost = inverse_edges[next][i].second;
      if (inverse_table[adj] > cost + dist) {
        inverse_table[adj] = cost + dist;
        rq.push({inverse_table[adj], adj});
      }
    }
  }
  int ans = 0;
  for (int i = 1; i <= N; i++) {
    ans = max(table[i] + inverse_table[i], ans);
  }
  cout << ans;
}
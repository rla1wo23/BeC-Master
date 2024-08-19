#include <iostream>
#define INF 1000000005
using namespace std;

int n, m;
int board[101][101] = {0};
int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      board[i][j] = INF;
      if (i == j) {
        board[i][j] = 0;
      }
    }
  }
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    board[a][b] = min(c, board[a][b]);
  }
  for (int i = 1; i <= n; i++) {
    for (int s = 1; s <= n; s++) {
      for (int e = 1; e <= n; e++) {
        board[s][e] = min(board[s][e], board[s][i] + board[i][e]);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (board[i][j] == INF) {
        cout << 0 << " ";
      } else {
        cout << board[i][j] << " ";
      }
    }
    cout << "\n";
  }
}
#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
struct Node {
  int x, y;   // 좌표
  float g, h; // g: 시작점부터 현재 노드까지의 비용, h:휴리스틱 값(추정 근사값)
  Node *parent;                     // 이전 노드 경로
  float f() const { return g + h; } // f = g + h
  bool operator<(const Node &other) const {
    return f() > other.f(); // pq에서 최소 f값을 우선하게끔, 비교 연산자 정의
  }
};
// 2차원 그리드 맵
vector<vector<int>> grid;
// 상하좌우 방향
const vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
// 휴리스틱 거리 추정함수
float h(int x1, int y1, int x2, int y2) { return abs(x1 - x2) + abs(y1 - y2); }

bool isValid(int x, int y) { // 탐색 가능한 경로인지
  int rows = grid.size();
  int cols = grid[0].size();
  return x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 0;
}

vector<pair<int, int>> aStar(pair<int, int> start, pair<int, int> goal) {
  int rows = grid.size();
  int cols = grid[0].size();

  priority_queue<Node> openList; // 우선순위 큐 (f값이 낮은 노드부터 처리)
  vector<vector<bool>> closedList(rows, vector<bool>(cols, false));

  // 시작 노드 초기화
  Node *startNode =
      new Node{start.first, start.second, 0.0f,
               h(start.first, start.second, goal.first, goal.second), nullptr};
  openList.push(*startNode);

  while (!openList.empty()) {
    Node current = openList.top();
    openList.pop();

    if (closedList[current.x][current.y])
      continue;
    closedList[current.x][current.y] = true;

    // 목표에 도달
    if (current.x == goal.first && current.y == goal.second) {
      vector<pair<int, int>> path;
      Node *pathNode = &current;
      while (pathNode) {
        path.emplace_back(pathNode->x, pathNode->y);
        pathNode = pathNode->parent;
      }
      reverse(path.begin(), path.end());
      return path;
    }

    // 현재 노드의 이웃 노드 탐색
    for (const auto &dir : directions) {
      int nx = current.x + dir.first;
      int ny = current.y + dir.second;

      if (isValid(nx, ny) && !closedList[nx][ny]) {
        Node *neighbor =
            new Node{nx, ny, current.g + 1, h(nx, ny, goal.first, goal.second),
                     new Node(current)};
        openList.push(*neighbor);
      }
    }
  }

  return {}; // 경로를 찾을 수 없을 경우 빈 벡터 반환
}

int main() {
  int choice;
  cout << "Choose an option:\n";
  cout << "1. Enter grid manually\n";
  cout << "2. Use default grid\n";
  cin >> choice;

  if (choice == 1) {
    int rows, cols;
    cout << "Enter grid dimensions (rows cols): ";
    cin >> rows >> cols;

    grid.resize(rows, vector<int>(cols));
    cout << "Enter grid (0 for open, 1 for obstacle):\n";
    cout << "Input format: Enter " << cols
         << " numbers per row, separated by spaces.\n";
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        cin >> grid[i][j];
      }
    }
  } else {
    // 기본 grid 설정
    grid = {
        {0, 1, 0, 0, 0}, {0, 1, 0, 1, 0}, {0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0}, {0, 0, 0, 0, 0},
    };
    cout << "Using default grid:\n";
    for (const auto &row : grid) {
      for (const auto &cell : row) {
        cout << cell << " ";
      }
      cout << "\n";
    }
  }

  pair<int, int> start, goal;
  cout << "Enter start coordinates (x y): ";
  cin >> start.first >> start.second;

  cout << "Enter goal coordinates (x y): ";
  cin >> goal.first >> goal.second;

  auto path = aStar(start, goal);

  if (!path.empty()) {
    cout << "Path found:\n";
    for (const auto &p : path) {
      cout << "(" << p.first << ", " << p.second << ") ";
    }
    cout << "\n";
  } else {
    cout << "No path found.\n";
  }

  return 0;
}

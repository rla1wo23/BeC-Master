#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

struct Node {
  int x, y; // 좌표
  float g, h; // g: 시작점부터 현재 노드까지의 비용, h: 휴리스틱(목표까지의 추정
              // 비용)
  Node *parent; // 이전 노드 포인터 (경로를 추적하는 데 사용)

  float f() const { return g + h; } // f = g + h

  bool operator<(const Node &other) const {
    return f() > other.f(); // 우선순위 큐에서 최소 f값을 우선
  }
};

// 글로벌 선언된 grid
std::vector<std::vector<int>> grid;

// 방향 벡터 (상, 하, 좌, 우)
const std::vector<std::pair<int, int>> directions = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// 휴리스틱 함수
float h(int x1, int y1, int x2, int y2) {
  return std::abs(x1 - x2) + std::abs(y1 - y2);
}

bool isValid(int x, int y) {
  int rows = grid.size();
  int cols = grid[0].size();
  return x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 0;
}

std::vector<std::pair<int, int>> aStar(std::pair<int, int> start,
                                       std::pair<int, int> goal) {
  int rows = grid.size();
  int cols = grid[0].size();

  std::priority_queue<Node> openList; // 우선순위 큐 (f값이 낮은 노드부터 처리)
  std::vector<std::vector<bool>> closedList(rows,
                                            std::vector<bool>(cols, false));

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
      std::vector<std::pair<int, int>> path;
      Node *pathNode = &current;
      while (pathNode) {
        path.emplace_back(pathNode->x, pathNode->y);
        pathNode = pathNode->parent;
      }
      std::reverse(path.begin(), path.end());
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
  std::cout << "Choose an option:\n";
  std::cout << "1. Enter grid manually\n";
  std::cout << "2. Use default grid\n";
  std::cin >> choice;

  if (choice == 1) {
    int rows, cols;
    std::cout << "Enter grid dimensions (rows cols): ";
    std::cin >> rows >> cols;

    grid.resize(rows, std::vector<int>(cols));
    std::cout << "Enter grid (0 for open, 1 for obstacle):\n";
    std::cout << "Input format: Enter " << cols
              << " numbers per row, separated by spaces.\n";
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        std::cin >> grid[i][j];
      }
    }
  } else {
    // 기본 grid 설정
    grid = {
        {0, 1, 0, 0, 0}, {0, 1, 0, 1, 0}, {0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0}, {0, 0, 0, 0, 0},
    };
    std::cout << "Using default grid:\n";
    for (const auto &row : grid) {
      for (const auto &cell : row) {
        std::cout << cell << " ";
      }
      std::cout << "\n";
    }
  }

  std::pair<int, int> start, goal;
  std::cout << "Enter start coordinates (x y): ";
  std::cin >> start.first >> start.second;

  std::cout << "Enter goal coordinates (x y): ";
  std::cin >> goal.first >> goal.second;

  auto path = aStar(start, goal);

  if (!path.empty()) {
    std::cout << "Path found:\n";
    for (const auto &p : path) {
      std::cout << "(" << p.first << ", " << p.second << ") ";
    }
    std::cout << "\n";
  } else {
    std::cout << "No path found.\n";
  }

  return 0;
}

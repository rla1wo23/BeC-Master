#include <iostream>
using namespace std;
int N, M1, M2, K;
int matrixA[100][100]; // N by M matrix
int matrixB[100][100]; // M by K matrix
int output[100][100];  // N by K matrix
int main() {
  // This program is to calculate the product of an N by M matrix "A"
  // and an M by K matrix "B".
  cin >> N >> M1; // input matrix A's size
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M1; j++) {
      cin >> matrixA[i][j];
    }
  }
  cin >> M2 >> K; // input matrix B's size
  if (M1 != M2) {
    cout << "it can't be calculated\n!";
    return 0;
  }
  for (int i = 0; i < M2; i++) {
    for (int j = 0; j < K; j++) {
      cin >> matrixB[i][j];
    }
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < K; j++) {
      for (int k = 0; k < M1; k++) {
        output[i][j] += matrixA[i][k] * matrixB[k][j];
      }
    }
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < K; j++) {
      cout << output[i][j] << " ";
    }
    cout << "\n";
  }
}

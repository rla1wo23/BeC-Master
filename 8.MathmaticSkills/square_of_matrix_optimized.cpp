#include <iostream>
using namespace std;
long long N, B; // maximum is 5 by 5 matrix
struct mat {
  long long matrix[5][5];
  void print() {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        cout << matrix[i][j] % 1000 << " ";
      }
      cout << "\n";
    }
  }
  void clear() {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        matrix[i][j] = 0;
      }
    }
  }
};
mat A; // default matrix
mat mult(mat left, mat right) {
  mat m;
  m.clear();
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        m.matrix[i][j] += (left.matrix[i][k] * right.matrix[k][j]) % 1000;
        m.matrix[i][j] %= 1000;
      }
    }
  }
  return m;
}
mat div(long long K) {
  if (K == 1) {
    return A;
  } else {
    mat half = div(K / 2);
    if (K % 2 == 0) {
      return mult(half, half);
    } else {
      return mult(A, mult(half, half));
    }
  }
}
int main() { // This program is to calculate the square of N by N matrix, we
             // will calculate N^B matrix
  cin >> N >> B;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> A.matrix[i][j];
    }
  }
  div(B).print();
}
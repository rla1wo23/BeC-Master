#include <iostream>
using namespace std;
long long output[5][5];
long long matrix[5][5]; // maximum is 5 by 5 matrix

int main() { // This program is to calculate the square of N by N matrix
  int N, B;  // we will calculate N^B matrix
  cin >> N >> B;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> matrix[i][j];
      output[i][j] = matrix[i][j];
    }
  }
  for (int t = 1; t < B; t++) {
    long long tmp[5][5] = {0};
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {
          tmp[i][j] += ((matrix[i][k]) * (output[k][j])) % 1000;
          tmp[i][j] %= 1000;
        }
      }
    }
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        output[i][j] = tmp[i][j];
      }
    }
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cout << output[i][j] % 1000 << " ";
    }
    cout << "\n";
  }
}
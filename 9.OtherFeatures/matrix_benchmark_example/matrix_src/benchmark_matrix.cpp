#include <benchmark/benchmark.h>
#include <cstdlib>
#include <vector>

void matrixMultiply(const std::vector<std::vector<int>> &A,
                    const std::vector<std::vector<int>> &B,
                    std::vector<std::vector<int>> &C) {
  int N = A.size();
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      C[i][j] = 0;
      for (int k = 0; k < N; ++k) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}

static void BM_MatrixMultiply(benchmark::State &state) {
  const int N = 500; // Matrix size (N x N)
  std::vector<std::vector<int>> A(N, std::vector<int>(N, rand() % 100));
  std::vector<std::vector<int>> B(N, std::vector<int>(N, rand() % 100));
  std::vector<std::vector<int>> C(N, std::vector<int>(N, 0));

  for (auto _ : state) {
    matrixMultiply(A, B, C);
  }
}

BENCHMARK(BM_MatrixMultiply)->Unit(benchmark::kMillisecond);
BENCHMARK_MAIN();

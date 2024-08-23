// good blog post: https://tinyurl.com/yn4hem7c
// solution fo leetcode 1143
class Solution {
public:
  int longestCommonSubsequence(string text1, string text2) {
    int N = text1.size();
    int M = text2.size();
    int dp[1001][1001];
    for (int i = 0; i <= N; i++) {
      dp[i][0] = 0;
      dp[0][i] = 0;
    }
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= M; j++) {
        if (text1[i - 1] == text2[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1] + 1;
        } else {
          dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
      }
    }
    return dp[N][M];
  }
};